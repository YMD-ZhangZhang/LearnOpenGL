#pragma once

#include "../ZShader.hpp"
#include "../Texture2D.hpp"

class Material
{
public:
	Material(const char* vsPath, const char* fsPath);
	ZShader* getShader();
	void setDepthTest(bool depthTest);
	void setDepthTestFunc(unsigned int func);
	void onSetRenderState();
	void setTexture(Texture2D* texture);
	Texture2D* getTexture();

private:
	void createShader(const char* vsPath, const char* fsPath);

private:
	Texture2D* _texture;
	ZShader* _shader;
	bool _depthTest;
	unsigned int _depthTestFunc;
};