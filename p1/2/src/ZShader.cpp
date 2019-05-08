#include "ZShader.hpp"

ZShader::ZShader(const char* vertexPath, const char* fragmentPath)
{
	std::string vsCode = this->loadShaderCode(vertexPath);
	std::string fsCode = this->loadShaderCode(fragmentPath);
	unsigned int vs = this->createVS(vsCode.c_str());
	unsigned int fs = this->createFS(fsCode.c_str());
	this->createProgram(vs, fs);
}

// ���ļ�����shaderԴ��
std::string ZShader::loadShaderCode(const char* path)
{
	std::string codeStr;
	std::ifstream shaderFile;
	shaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	try
	{
		// ���ļ�
		shaderFile.open(path);
		std::stringstream shaderStream;
		// ��ȡ�ļ��Ļ������ݵ���������
		shaderStream << shaderFile.rdbuf();
		// �ر��ļ�������
		shaderFile.close();
		// ת����������string
		codeStr = shaderStream.str();
	}
	catch (std::ifstream::failure e)
	{
		std::cout << "����shader�ļ�ʧ��" << std::endl;
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
		std::cout << "����vs��������\n" << infoLog << std::endl;
	}
	else
	{
		std::cout << "����vs�ɹ�" << std::endl;
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
		std::cout << "����fs��������\n" << infoLog << std::endl;
	}
	else
	{
		std::cout << "����fs�ɹ�" << std::endl;
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
		std::cout << "����program��������\n" << infoLog << std::endl;
	}
	else
	{
		std::cout << "����program�ɹ�" << std::endl;
	}

	this->_shaderProgram = shaderProgram;
	glDeleteShader(vs);
	glDeleteShader(fs);
}

void ZShader::use()
{
	glUseProgram(this->_shaderProgram);
}
