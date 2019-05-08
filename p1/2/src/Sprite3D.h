#pragma once

#include "core/Node3D.h"
#include "Texture2D.hpp"
#include "ZShader.hpp"
#include "Engine.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace std;

class Sprite3D : public Node3D
{
public:
	Sprite3D();
	void loadTexture(const char* url);
	virtual void onRender(Camera* camera);

private:
	void createShader();
	void createVBO();
	void createVAO();

private:
	ZShader* _shader;
	Texture2D* _texture;
	unsigned int _vbo;
	unsigned int _vao;
};