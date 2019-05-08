#pragma once

#include "Node.h"
#include "Texture2D.hpp"
#include "Engine.h"
#include "core/Material.h"

using namespace std;

class Sprite : public Node
{
public:
	Sprite();
	void loadTexture(const char* url);
	virtual void onRender(Camera* camera);

private:
	void createVBO();
	void createVAO();

private:
	Material* _material;
	Texture2D* _texture;
	unsigned int _vbo;
	unsigned int _vao;
};