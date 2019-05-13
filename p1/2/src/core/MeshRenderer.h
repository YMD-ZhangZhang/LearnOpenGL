#pragma once

#include "../Camera.h"
#include "Mesh.h"
#include "Material.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

class MeshRenderer
{
public:
	MeshRenderer();
	void loadDefaultMesh();
	void onRender(Camera* camera);
	Material* getMaterial();
	void addMesh(Mesh mesh);

private:
	void renderSingleMesh(Camera* camera, Mesh mesh);
	void createVBO(Mesh mesh);
	void createEBO(Mesh mesh);
	void createVAO();

	void processNode(aiNode *node, const aiScene *scene);
	Mesh processMesh(aiMesh *mesh, const aiScene *scene);
	vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, string typeName);

private:
	Material* _material;
	unsigned int _vbo;
	unsigned int _ebo;
	unsigned int _vao;
	vector<Mesh> meshes;
};