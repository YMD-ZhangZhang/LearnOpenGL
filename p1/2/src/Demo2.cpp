#include "Demo2.h"

Demo2::Demo2()
{
	Engine::getInstance()->init(480, 320);

	Node* node = new Node();
	node->setName("node1");

	Sprite* sprite = new Sprite();
	sprite->setName("sprite");
	sprite->setX(50);
	sprite->setY(-50);
	sprite->loadTexture(".\\texture\\demo2_1.png");
	node->addChild(sprite);

	Sprite* sprite2 = new Sprite();
	sprite2->setName("sprite2");
	sprite2->setX(100);
	sprite2->setY(-100);
	sprite2->loadTexture(".\\texture\\demo2.png");
	node->addChild(sprite2);

	Scene* scene = new Scene();
	scene->addChild(node);
	Engine::getInstance()->addScene(scene);

	Engine::getInstance()->beginRenderLoop();
}
