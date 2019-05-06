#ifndef __Texture2D_H__
#define __Texture2D_H__

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Texture2D
{
private:
	int _width, _height, _nrChannels;
	unsigned char* _data;
	unsigned int _glTexture;

public:
	Texture2D(const char* url);
	unsigned char* getData();
	int getWidth();
	int getHeight();
	unsigned int getGLTexture();
	void bindTexture();
	void texImage2D();
	void texParameteri();
	void dispose();
	void deleteTexture();
};

#endif