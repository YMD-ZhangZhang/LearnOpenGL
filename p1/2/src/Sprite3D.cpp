#include "Sprite3D.h"

Sprite3D::Sprite3D()
{
	_meshRenderer = new MeshRenderer();
}

void Sprite3D::loadTexture(const char * url)
{
	_texture = new Texture2D(url);
	_texture->bindTexture();
	_texture->texImage2D();
	_texture->texParameteri();
	_meshRenderer->getMaterial()->setTexture(_texture);
}

void Sprite3D::onRender(Camera* camera)
{
	_meshRenderer->onRender(camera);
	Node::onRender(camera);
}
