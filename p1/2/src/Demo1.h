#ifndef __Demo1_H__
#define __Demo1_H__

#include "ZOpenGL.hpp"
#include "ZShader.hpp"
#include "Texture2D.hpp"
#include "IRenderLoop.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Demo1 : public IRenderLoop
{
public:
	Demo1();

private:
	void onRenderLoop(GLFWwindow* window);
	void processInput(GLFWwindow *window);
	void onRender(ZShader* shaderObj);
	unsigned int createBoxVBO();
	unsigned int createObjVAO(unsigned int boxVBO);
	void loadDiffuseTexture();
	void loadSpecularTexture();
	void renderObj(unsigned int objVAO, ZShader* shader);

private:
	bool init;
	char* vsPath;
	char* fsPath;
	ZShader *shaderObj;
};

#endif
