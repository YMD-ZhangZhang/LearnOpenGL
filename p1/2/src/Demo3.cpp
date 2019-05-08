#include "Demo3.h"

Demo3::Demo3()
{
	Engine::getInstance()->init(480, 320);

	Node* node = new Node();
	node->setName("node1");

	Sprite3D* sprite = new Sprite3D();
	sprite->setName("sprite3d");
	sprite->setX(50);
	sprite->setY(-50);
	sprite->loadTexture(".\\texture\\container2.png");
	node->addChild(sprite);

	/*Sprite* sprite2 = new Sprite();
	sprite2->setName("sprite2");
	sprite2->setX(100);
	sprite2->setY(-100);
	sprite2->loadTexture(".\\texture\\demo2.png");
	node->addChild(sprite2);*/

	Scene3D* scene = new Scene3D();
	scene->addChild(node);
	Engine::getInstance()->addScene(scene);

	Camera* camera = new Camera();
	camera->setName("camera");
	camera->transform->x = 1.0f;
	camera->transform->y = 1.0f;
	camera->transform->z = 5.0f;
	scene->setCamera(camera);

	Engine::getInstance()->beginRenderLoop();
}
