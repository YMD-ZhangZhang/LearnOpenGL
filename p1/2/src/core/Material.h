#pragma once

#include "../ZShader.hpp"

class Material
{
public:
	Material(const char* vsPath, const char* fsPath);
	ZShader* getShader();

private:
	void createShader(const char* vsPath, const char* fsPath);

private:
	ZShader* _shader;
};