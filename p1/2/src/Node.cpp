#include "Node.h"

Node::Node()
{
	_name = "noname";
}

Node::~Node()
{
}

void Node::setName(string name)
{
	_name = name;
}

string Node::getName()
{
	return _name;
}

void Node::setX(int x)
{
	_x = x;
}

void Node::setY(int y)
{
	_y = y;
}

int Node::getX()
{
	return _x;
}

int Node::getY()
{
	return _y;
}

int Node::getWidth()
{
	return 100;
}

int Node::getHeight()
{
	return 100;
}

void Node::addChild(Node * child)
{
	child->setParent(this);
	_childs.push_back(child);
}

void Node::removeChild(Node * child)
{
	child->setParent(nullptr);

	for (vector<Node*>::iterator it = _childs.begin(); it != _childs.end();)
	{
		if (*it == child)
		{
			it = _childs.erase(it);
		}
		else
		{
			++it;
		}
	}
}

vector<Node*> Node::getChilds()
{
	return _childs;
}

void Node::onRender(Camera* camera)
{
	//std::cout << "ÕýÔÚäÖÈ¾:" << this->_name << std::endl;
	for (vector<Node*>::iterator it = _childs.begin(); it != _childs.end();)
	{
		(*it)->onRender(camera);
		++it;
	}
}

Node * Node::getParent()
{
	return _parent;
}

void Node::setParent(Node * parent)
{
	_parent = parent;
}
