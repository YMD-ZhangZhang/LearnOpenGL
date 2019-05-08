#pragma once

#include "Node.h"
#include "Camera.h"

class BaseScene : public Node
{
public:
	void setCamera(Camera* camera);
	Camera* getCamera();
	void onSceneRender();

private:
	Camera* _camera;
};