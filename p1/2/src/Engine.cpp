#include "Engine.h"

Engine* Engine::_instance = nullptr;

Engine * Engine::getInstance()
{
	if (Engine::_instance == nullptr)
	{
		Engine::_instance = new Engine();
	}
	return Engine::_instance;
}

void Engine::init(int width, int height)
{
	_width = width;
	_height = height;
	ZOpenGL::init(this, width, height);
}

void Engine::beginRenderLoop()
{
	// 循环
	while (!glfwWindowShouldClose(window))
	{
		onRenderLoop(window);

		// 交换缓冲区
		glfwSwapBuffers(window);

		// 事件
		glfwPollEvents();
	}

	glfwTerminate();
}

void Engine::onRenderLoop(GLFWwindow * window)
{
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	for (vector<BaseScene*>::iterator it = _sceneList.begin(); it != _sceneList.end();)
	{
		(*it)->onSceneRender();
		++it;
	}
}

void Engine::setGLFWwindow(GLFWwindow * window)
{
	this->window = window;
}

void Engine::addScene(BaseScene * scene)
{
	_sceneList.push_back(scene);
}

int Engine::getWidth()
{
	return _width;
}

int Engine::getHeight()
{
	return _height;
}
