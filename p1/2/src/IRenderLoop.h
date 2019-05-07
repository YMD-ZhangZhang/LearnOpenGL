#ifndef __IRenderLoop_H__
#define __IRenderLoop_H__

#include <glad/glad.h>
#include <GLFW/glfw3.h>
class IRenderLoop
{
public:
	virtual void onRenderLoop(GLFWwindow * window);
	virtual void setGLFWwindow(GLFWwindow* window);
};

#endif