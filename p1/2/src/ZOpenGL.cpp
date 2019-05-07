#include "ZOpenGL.hpp"

void ZOpenGL::init(IRenderLoop* iRenderLoop, int width, int height)
{
	GLFWwindow* window;

	// ��ʼ����
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// ��������������
	window = glfwCreateWindow(width, height, "OpenGL Window", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return;
	}

	// ���õ�ǰ����������
	glfwMakeContextCurrent(window);

	// ��ʼ��glad
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		return;
	}

	glEnable(GL_DEPTH_TEST);
	iRenderLoop->setGLFWwindow(window);

	/*
	// ѭ��
	while (!glfwWindowShouldClose(window))
	{
		iRenderLoop->onRenderLoop(window);

		// ����������
		glfwSwapBuffers(window);

		// �¼�
		glfwPollEvents();
	}

	glfwTerminate();
	*/
}
