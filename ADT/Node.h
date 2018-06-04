#pragma once
#include "../Enemies/Enemy.h";

class Node
{
	Enemy* pointer;
	Node * next;
public:
	Node();
	Node(Enemy* newPtr);
	Node(Enemy* newPtr, Node *nextNodePtr);
	void setPtr(Enemy * newPtr);
	void setNextNode(Node *nextNodePtr);
	Enemy* getItem() const ;
	Node * getNextPtr() const ;
	string getInfo() const ;	//get Info of Enemy (item)
};
