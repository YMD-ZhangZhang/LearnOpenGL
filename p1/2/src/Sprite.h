#pragma once

#include "Node.h"
#include "Texture2D.hpp"
#include "ZShader.hpp"
#include "Engine.h"

using namespace std;

class Sprite : public Node
{
public:
	Sprite();
	void loadTexture(const char* url);
	virtual void onRender();

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