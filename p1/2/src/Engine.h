#pragma once

#include "BaseScene.h"
#include "IRenderLoop.h"
#include "ZOpenGL.hpp"
#include <vector>

using namespace std;

class Engine : public IRenderLoop
{
public:
	static Engine* _instance;
	static Engine* getInstance();
	void init(int width, int height);
	void beginRenderLoop();
	void addScene(BaseScene* scene);
	int getWidth();
	int getHeight();

private:
	void onRenderLoop(GLFWwindow* window);
	void setGLFWwindow(GLFWwindow* window);

private:
	int _width;
	int _height;
	vector<BaseScene*> _sceneList;
	GLFWwindow* window;
};