#include "Material.h"

Material::Material(const char* vsPath, const char* fsPath)
{
	this->createShader(vsPath, fsPath);
}

ZShader * Material::getShader()
{
	return _shader;
}

void Material::createShader(const char* vsPath, const char* fsPath)
{
	this->_shader = new ZShader(vsPath, fsPath);
}