#include "Sprite3D.h"

Sprite3D::Sprite3D()
{
	this->createShader();
}

void Sprite3D::loadTexture(const char * url)
{
	//glActiveTexture(GL_TEXTURE0);

	_texture = new Texture2D(url);
	_texture->bindTexture();
	_texture->texImage2D();
	_texture->texParameteri();

	//_texture->dispose();
}

void Sprite3D::onRender(Camera* camera)
{
	// 使用shader
	this->_shader->use();

	// 根据实时位置生成顶点 并提交
	this->createVBO();
	this->createVAO();
	glBindVertexArray(this->_vao);

	// 模型矩阵
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::rotate(model, glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));
	this->_shader->setUniformMatrix4fv("model", 1, GL_FALSE, glm::value_ptr(model));

	// 观察矩阵
	glm::mat4 view = glm::mat4(1.0f);
	//view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
	view = glm::translate(view, glm::vec3(-camera->transform->x, -camera->transform->y, -camera->transform->z));
	this->_shader->setUniformMatrix4fv("view", 1, GL_FALSE, glm::value_ptr(view));

	// 投影矩阵
	glm::mat4 projection = glm::mat4(1.0f);
	projection = glm::perspective(glm::radians(45.0f), (float)480 / 320, 0.1f, 100.0f);
	this->_shader->setUniformMatrix4fv("projection", 1, GL_FALSE, glm::value_ptr(projection));

	// base
	this->_shader->setUniform3f("lightPos", 1.2f, 1.0f, 2.0f);
	this->_shader->setUniform3f("viewPos", camera->transform->x, camera->transform->y, camera->transform->z);

	// light
	this->_shader->setUniform3f("light.ambient", 0.2f, 0.2f, 0.2f);
	this->_shader->setUniform3f("light.diffuse", 0.8f, 0.8f, 0.8f);
	this->_shader->setUniform3f("light.specular", 1.0f, 1.0f, 1.0f);

	// material
	this->_shader->setUniform1i("material.diffuse", 0);
	this->_shader->setUniform1i("material.specular", 0);
	this->_shader->setUniform1f("material.shininess", 50.0f);

	// 绑定纹理
	_texture->bindTexture();

	// 绘制
	glDrawArrays(GL_TRIANGLES, 0, 36);

	Node::onRender(camera);
}

void Sprite3D::createShader()
{
	const char* vsPath = ".\\shader\\d3vs.txt";
	const char* fsPath = ".\\shader\\d3fs.txt";
	this->_shader = new ZShader(vsPath, fsPath);
}

void Sprite3D::createVBO()
{
	float vertices[] = {
		// positions          // normals           // texture coords
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
		0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
		0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
		0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,

		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,
		0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,

		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

		0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
		0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
		0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
		0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
		0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
		0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f
	};

	// VBO
	unsigned int VBO;
	glGenBuffers(1, &VBO);

	// VBO base data
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// dispose
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	this->_vbo = VBO;
}

void Sprite3D::createVAO()
{
	// 顶点数组对象 VAO
	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	// VBO
	glBindBuffer(GL_ARRAY_BUFFER, this->_vbo);

	// VBO add data 顶点坐标
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// VBO add data 法线
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	// VBO add data 纹理
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	this->_vao = VAO;
}
