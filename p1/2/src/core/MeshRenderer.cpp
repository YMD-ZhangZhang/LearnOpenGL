#include "MeshRenderer.h"

MeshRenderer::MeshRenderer()
{
	_material = new Material(".\\shader\\modelvs.txt", ".\\shader\\modelfs.txt");
	_material->setDepthTest(true);
	_material->setDepthTestFunc(GL_LESS);
	//loadDefaultMesh();
}

void MeshRenderer::onRender(Camera * camera, Transform* transform)
{
	// 使用shader
	_material->getShader()->use();
	_material->onSetRenderState();

	for (vector<Mesh>::iterator it = this->meshes.begin(); it != this->meshes.end(); ++it)
	{
		this->renderSingleMesh(camera, *it, transform);
	}
}

Material * MeshRenderer::getMaterial()
{
	return _material;
}

void MeshRenderer::addMesh(Mesh mesh)
{
	meshes.push_back(mesh);
}

void MeshRenderer::loadDefaultMesh()
{
	Assimp::Importer importer;
	const aiScene *scene = importer.ReadFile(".\\model\\d.fbx", aiProcess_Triangulate | aiProcess_FlipUVs);

	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		cout << "ERROR::ASSIMP::" << importer.GetErrorString() << endl;
	}

	processNode(scene->mRootNode, scene);
	cout << "加载模型完成::" << endl;
}

void MeshRenderer::renderSingleMesh(Camera * camera, Mesh mesh, Transform* transform)
{
	// 根据实时位置生成顶点 并提交
	this->createVBO(mesh);
	this->createEBO(mesh);
	this->createVAO();
	glBindVertexArray(this->_vao);

	// 模型矩阵
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::scale(model, transform->localScale);
	model = glm::translate(model, transform->localPosition);
	model = glm::rotate(model, glm::radians(transform->localRotationEuler.x), glm::vec3(1.0f, 0.0f, 0.0f));
	model = glm::rotate(model, glm::radians(transform->localRotationEuler.y), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::rotate(model, glm::radians(transform->localRotationEuler.z), glm::vec3(0.0f, 0.0f, 1.0f));
	this->_material->getShader()->setUniformMatrix4fv("model", 1, GL_FALSE, glm::value_ptr(model));

	// 观察矩阵
	glm::mat4 view = glm::mat4(1.0f);
	//view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
	view = glm::translate(view, glm::vec3(-camera->transform->localPosition.x, -camera->transform->localPosition.y, -camera->transform->localPosition.z));
	this->_material->getShader()->setUniformMatrix4fv("view", 1, GL_FALSE, glm::value_ptr(view));

	// 投影矩阵
	glm::mat4 projection = glm::mat4(1.0f);
	projection = glm::perspective(glm::radians(45.0f), (float)480 / 320, 0.1f, 1000.0f);
	this->_material->getShader()->setUniformMatrix4fv("projection", 1, GL_FALSE, glm::value_ptr(projection));

	// base
	//this->_material->getShader()->setUniform3f("lightPos", 1.2f, 1.0f, 2.0f);
	//this->_material->getShader()->setUniform3f("viewPos", camera->transform->x, camera->transform->y, camera->transform->z);

	// light
	//this->_material->getShader()->setUniform3f("light.ambient", 0.2f, 0.2f, 0.2f);
	//this->_material->getShader()->setUniform3f("light.diffuse", 0.8f, 0.8f, 0.8f);
	//this->_material->getShader()->setUniform3f("light.specular", 1.0f, 1.0f, 1.0f);

	// material
	this->_material->getShader()->setUniform1i("material.diffuse", 0);
	this->_material->getShader()->setUniform1i("material.specular", 0);
	this->_material->getShader()->setUniform1f("material.shininess", 50.0f);

	// 绑定纹理
	this->_material->getTexture()->bindTexture();

	// 绘制
	glDrawArrays(GL_TRIANGLES, 0, 36);
	//glDrawElements(GL_TRIANGLES, mesh.indices.size(), GL_UNSIGNED_INT, 0);
}

void MeshRenderer::createVBO(Mesh mesh)
{
	unsigned int VBO;
	glGenBuffers(1, &VBO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, mesh.vertices.size() * sizeof(Vertex), &(mesh.vertices[0]), GL_STATIC_DRAW);

	this->_vbo = VBO;
}

void MeshRenderer::createEBO(Mesh mesh)
{
	unsigned int EBO;
	glGenBuffers(1, &EBO);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh.indices.size() * sizeof(unsigned int), &(mesh.indices[0]), GL_STATIC_DRAW);

	this->_ebo = EBO;
}

void MeshRenderer::createVAO()
{
	// 顶点数组对象 VAO
	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	// VBO
	glBindBuffer(GL_ARRAY_BUFFER, this->_vbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->_ebo);

	// VBO add data 顶点坐标
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
	glEnableVertexAttribArray(0);

	// VBO add data 法线
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));
	glEnableVertexAttribArray(1);

	// VBO add data 纹理
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));
	glEnableVertexAttribArray(2);

	this->_vao = VAO;
}

void MeshRenderer::processNode(aiNode * node, const aiScene * scene)
{
	// 处理节点所有的网格（如果有的话）
	for (unsigned int i = 0; i < node->mNumMeshes; i++)
	{
		aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
		meshes.push_back(processMesh(mesh, scene));
	}

	// 接下来对它的子节点重复这一过程
	for (unsigned int i = 0; i < node->mNumChildren; i++)
	{
		processNode(node->mChildren[i], scene);
	}
}

Mesh MeshRenderer::processMesh(aiMesh * mesh, const aiScene * scene)
{
	vector<Vertex> vertices;
	vector<unsigned int> indices;
	vector<Texture> textures;

	// 顶点数据
	for (unsigned int i = 0; i < mesh->mNumVertices; i++)
	{
		Vertex vertex;

		glm::vec3 vector;

		// 顶点位置
		vector.x = mesh->mVertices[i].x;
		vector.y = mesh->mVertices[i].y;
		vector.z = mesh->mVertices[i].z;
		vertex.Position = vector;

		// 法线
		vector.x = mesh->mNormals[i].x;
		vector.y = mesh->mNormals[i].y;
		vector.z = mesh->mNormals[i].z;
		vertex.Normal = vector;

		// 纹理坐标
		if (mesh->mTextureCoords[0]) // 网格是否有纹理坐标？
		{
			glm::vec2 vec;
			vec.x = mesh->mTextureCoords[0][i].x;
			vec.y = mesh->mTextureCoords[0][i].y;
			vertex.TexCoords = vec;
		}
		else
			vertex.TexCoords = glm::vec2(0.0f, 0.0f);

		vertices.push_back(vertex);
	}

	// 索引
	for (unsigned int i = 0; i < mesh->mNumFaces; i++)
	{
		aiFace face = mesh->mFaces[i];
		for (unsigned int j = 0; j < face.mNumIndices; j++)
			indices.push_back(face.mIndices[j]);
	}

	// 处理材质
	if (mesh->mMaterialIndex >= 0)
	{
		aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex];

		vector<Texture> diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");

		textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());

		vector<Texture> specularMaps = loadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");

		textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
	}

	return Mesh(vertices, indices, textures);
}

vector<Texture> MeshRenderer::loadMaterialTextures(aiMaterial * mat, aiTextureType type, string typeName)
{
	vector<Texture> textures;
	for (unsigned int i = 0; i < mat->GetTextureCount(type); i++)
	{
		aiString str;
		mat->GetTexture(type, i, &str);

		Texture texture;
		//texture.id = TextureFromFile(str.C_Str(), directory);
		//texture.type = typeName;
		//texture.path = str;
		textures.push_back(texture);
	}
	return textures;
}
