#include "BaseScene.h"

void BaseScene::setCamera(Camera * camera)
{
	_camera = camera;
}

Camera * BaseScene::getCamera()
{
	return _camera;
}

void BaseScene::onSceneRender()
{
	Node::onRender(_camera);
}
