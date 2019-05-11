#pragma once

#include "core/Node3D.h"
#include "Texture2D.hpp"
#include "Engine.h"
#include "core/MeshRenderer.h"

using namespace std;

class Sprite3D : public Node3D
{
public:
	Sprite3D();
	void loadTexture(const char* url);
	virtual void onRender(Camera* camera);

private:
	Texture2D* _texture;
	MeshRenderer* _meshRenderer;
};