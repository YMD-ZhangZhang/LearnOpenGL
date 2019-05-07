#include "ZOpenGL.hpp"

void ZOpenGL::init(IRenderLoop* iRenderLoop, int width, int height)
{
	GLFWwindow* window;

	// 初始化库
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// 创建窗口上下文
	window = glfwCreateWindow(width, height, "OpenGL Window", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return;
	}

	// 设置当前窗口上下文
	glfwMakeContextCurrent(window);

	// 初始化glad
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		return;
	}

	glEnable(GL_DEPTH_TEST);
	iRenderLoop->setGLFWwindow(window);

	/*
	// 循环
	while (!glfwWindowShouldClose(window))
	{
		iRenderLoop->onRenderLoop(window);

		// 交换缓冲区
		glfwSwapBuffers(window);

		// 事件
		glfwPollEvents();
	}

	glfwTerminate();
	*/
}
