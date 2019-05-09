#pragma once

#include "core/Node3D.h"
#include "Texture2D.hpp"
#include "core/Material.h"
#include "Engine.h"
#include "core/Mesh.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

using namespace std;

class Sprite3D : public Node3D
{
public:
	Sprite3D();
	void loadTexture(const char* url);
	virtual void onRender(Camera* camera);

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
	Texture2D* _texture;
	unsigned int _vbo;
	unsigned int _ebo;
	unsigned int _vao;
	vector<Mesh> meshes;
};