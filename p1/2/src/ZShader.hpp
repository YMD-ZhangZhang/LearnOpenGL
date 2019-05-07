#ifndef __ZShader_H__
#define __ZShader_H__

#include <iostream>
#include <glad/glad.h> 
//#include <GLFW/glfw3.h>
#include <fstream>
#include <sstream>

class ZShader
{
public:
	ZShader(const char* vertexPath, const char* fragmentPath);
	void use();
	unsigned int getShader();
	void setUniform1i(const GLchar *name, GLint v0);
	void setUniform3f(const GLchar *name, GLfloat v0, GLfloat v1, GLfloat v2);
	void setUniformMatrix4fv(const GLchar *name, GLsizei count, GLboolean transpose, const GLfloat *value);

private:
	// 从文件加载shader源码
	std::string loadShaderCode(const char* path);
	unsigned int createVS(const char* code);
	unsigned int createFS(const char* code);
	void createProgram(unsigned int vs, unsigned int fs);

private:
	unsigned int _shaderProgram;
};

#endif
