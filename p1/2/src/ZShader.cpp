#include "ZShader.hpp"

ZShader::ZShader(const char* vertexPath, const char* fragmentPath)
{
	std::string vsCode = this->loadShaderCode(vertexPath);
	std::string fsCode = this->loadShaderCode(fragmentPath);
	unsigned int vs = this->createVS(vsCode.c_str());
	unsigned int fs = this->createFS(fsCode.c_str());
	this->createProgram(vs, fs);
}

// 从文件加载shader源码
std::string ZShader::loadShaderCode(const char* path)
{
	std::string codeStr;
	std::ifstream shaderFile;
	shaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	try
	{
		// 打开文件
		shaderFile.open(path);
		std::stringstream shaderStream;
		// 读取文件的缓冲内容到数据流中
		shaderStream << shaderFile.rdbuf();
		// 关闭文件处理器
		shaderFile.close();
		// 转换数据流到string
		codeStr = shaderStream.str();
	}
	catch (std::ifstream::failure e)
	{
		std::cout << "加载shader文件失败" << std::endl;
	}
	return codeStr;
}

unsigned int ZShader::getShader()
{
	return this->_shaderProgram;
}

void ZShader::setUniform1i(const GLchar * name, GLint v0)
{
	glUniform1i(glGetUniformLocation(this->_shaderProgram, name), v0);
}

void ZShader::setUniform1f(const GLchar * name, GLfloat v0)
{
	glUniform1f(glGetUniformLocation(this->_shaderProgram, name), v0);
}

void ZShader::setUniform3f(const GLchar * name, GLfloat v0, GLfloat v1, GLfloat v2)
{
	glUniform3f(glGetUniformLocation(this->_shaderProgram, name), v0, v1, v2);
}

void ZShader::setUniformMatrix4fv(const GLchar * name, GLsizei count, GLboolean transpose, const GLfloat * value)
{
	unsigned int transformLoc = glGetUniformLocation(this->_shaderProgram, name);
	glUniformMatrix4fv(transformLoc, count, transpose, value);
}

unsigned int ZShader::createVS(const char* code)
{
	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &code, NULL);
	glCompileShader(vertexShader);

	int success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "创建vs发生错误\n" << infoLog << std::endl;
	}
	else
	{
		std::cout << "创建vs成功" << std::endl;
	}

	return vertexShader;
}

unsigned int ZShader::createFS(const char* code)
{
	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &code, NULL);
	glCompileShader(fragmentShader);

	int success;
	char infoLog[512];
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "创建fs发生错误\n" << infoLog << std::endl;
	}
	else
	{
		std::cout << "创建fs成功" << std::endl;
	}

	return fragmentShader;
}

void ZShader::createProgram(unsigned int vs, unsigned int fs)
{
	unsigned int shaderProgram;
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vs);
	glAttachShader(shaderProgram, fs);
	glLinkProgram(shaderProgram);

	int success;
	char infoLog[512];
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "创建program发生错误\n" << infoLog << std::endl;
	}
	else
	{
		std::cout << "创建program成功" << std::endl;
	}

	this->_shaderProgram = shaderProgram;
	glDeleteShader(vs);
	glDeleteShader(fs);
}

void ZShader::use()
{
	glUseProgram(this->_shaderProgram);
}
