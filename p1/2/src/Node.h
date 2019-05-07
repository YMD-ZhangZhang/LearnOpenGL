#pragma once

#include <sstream>
#include <vector>
#include <iostream>

using namespace std;

class Node
{
public:
	Node();
	~Node();

	void setName(string name);
	string getName();

	void setX(int x);
	void setY(int y);
	int getX();
	int getY();
	int getWidth();
	int getHeight();

	void addChild(Node* child);
	void removeChild(Node* child);
	vector<Node*> getChilds();
	virtual void onRender();
	Node* getParent();
	void setParent(Node* parent);

private:
	string _name;
	int _x;
	int _y;
	Node* _parent;
	vector<Node*> _childs;
};

