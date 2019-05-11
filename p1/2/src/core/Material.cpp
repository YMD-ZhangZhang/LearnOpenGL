#include "Material.h"

Material::Material(const char* vsPath, const char* fsPath)
{
	this->createShader(vsPath, fsPath);

	_depthTest = false;
	_depthTestFunc = GL_LESS;
}

ZShader * Material::getShader()
{
	return _shader;
}

void Material::setDepthTest(bool depthTest)
{
	_depthTest = depthTest;
}

void Material::setDepthTestFunc(unsigned int func)
{
	_depthTestFunc = func;
}

void Material::onSetRenderState()
{
	if (_depthTest)
	{
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(_depthTestFunc);
	}
	else
	{
		glDisable(GL_DEPTH_TEST);
	}
}

void Material::setTexture(Texture2D * texture)
{
	_texture = texture;
}

Texture2D * Material::getTexture()
{
	return _texture;
}

void Material::createShader(const char* vsPath, const char* fsPath)
{
	this->_shader = new ZShader(vsPath, fsPath);
}