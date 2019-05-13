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

	sprite->getMeshRenderer()->addMesh(Mesh::createCube());
	node->addChild(sprite);

	// sprite2
	Sprite3D* sprite2 = new Sprite3D();
	sprite2->setName("sprite3d");
	sprite2->setX(50);
	sprite2->setY(-50);
	sprite2->loadTexture(".\\texture\\demo2.png");

	sprite2->getMeshRenderer()->addMesh(Mesh::createQuad());
	node->addChild(sprite2);

	// scene
	Scene3D* scene = new Scene3D();
	scene->addChild(node);
	Engine::getInstance()->addScene(scene);

	Camera* camera = new Camera();
	camera->setName("camera");
	camera->transform->x = 0.0f;
	camera->transform->y = 0.0f;
	camera->transform->z = 5.0f;
	scene->setCamera(camera);

	Engine::getInstance()->beginRenderLoop();
}
