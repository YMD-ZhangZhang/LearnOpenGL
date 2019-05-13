#include "Demo3.h"

Demo3::Demo3()
{
	Engine::getInstance()->init(480, 320);

	Node* node = new Node();
	node->setName("node1");

	// sprite1
	Sprite3D* sprite = new Sprite3D();
	sprite->setName("sprite3d");
	sprite->setX(50);
	sprite->setY(-50);
	sprite->loadTexture(".\\texture\\container2.png");

	sprite->transform->localScale.x = 0.5f;
	sprite->transform->localScale.y = 0.5f;
	sprite->transform->localScale.z = 0.5f;

	sprite->transform->localPosition.x = 1.0f;
	sprite->transform->localPosition.y = 0.0f;
	sprite->transform->localPosition.z = 0.0f;

	sprite->transform->localRotationEuler.x = 0.0f;
	sprite->transform->localRotationEuler.y = 0.0f;
	sprite->transform->localRotationEuler.z = 0.0f;

	sprite->getMeshRenderer()->addMesh(Mesh::createCube());
	node->addChild(sprite);

	// sprite2
	sprite = new Sprite3D();
	sprite->setName("sprite3d");
	sprite->setX(50);
	sprite->setY(-50);
	sprite->loadTexture(".\\texture\\container2.png");

	sprite->transform->localScale.x = 0.5f;
	sprite->transform->localScale.y = 0.5f;
	sprite->transform->localScale.z = 0.5f;

	sprite->transform->localPosition.x = -1.0f;
	sprite->transform->localPosition.y = 1.0f;
	sprite->transform->localPosition.z = 0.0f;

	sprite->transform->localRotationEuler.x = 0.0f;
	sprite->transform->localRotationEuler.y = 0.0f;
	sprite->transform->localRotationEuler.z = 0.0f;

	sprite->getMeshRenderer()->addMesh(Mesh::createCube());
	node->addChild(sprite);

	// scene
	Scene3D* scene = new Scene3D();
	scene->addChild(node);
	Engine::getInstance()->addScene(scene);

	Camera* camera = new Camera();
	camera->setName("camera");
	camera->transform->localPosition.x = 0.0f;
	camera->transform->localPosition.y = 1.0f;
	camera->transform->localPosition.z = 5.0f;
	scene->setCamera(camera);

	Engine::getInstance()->beginRenderLoop();
}
