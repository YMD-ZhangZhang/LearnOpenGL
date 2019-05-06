#include "Texture2D.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

Texture2D::Texture2D(const char* url)
{
	this->_data = stbi_load(url, &this->_width, &this->_height, &this->_nrChannels, 0);
	glGenTextures(1, &this->_glTexture);
}

unsigned char* Texture2D::getData()
{
	return this->_data;
}

int Texture2D::getWidth()
{
	return this->_width;
}

int Texture2D::getHeight()
{
	return this->_height;
}

unsigned int Texture2D::getGLTexture()
{
	return this->_glTexture;
}

void Texture2D::bindTexture()
{
	glBindTexture(GL_TEXTURE_2D, this->_glTexture);
}

void Texture2D::texImage2D()
{
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, this->_width, this->_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, this->_data);
}

void Texture2D::texParameteri()
{
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

void Texture2D::dispose()
{
	stbi_image_free(this->_data);
}

void Texture2D::deleteTexture()
{
	glDeleteTextures(1, &this->_glTexture);
}
