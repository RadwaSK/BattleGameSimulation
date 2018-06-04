#include "Node.h"

Node::Node(){
	pointer = nullptr;
	next = nullptr;
}

Node::Node(Enemy *newPtr){
	pointer = newPtr;
	next = nullptr;
}

Node::Node(Enemy *newPtr, Node *nextNodePtr){
	pointer = newPtr;
	next = nextNodePtr;
}

void Node::setPtr(Enemy *newPtr){
	pointer = newPtr;
}

void Node::setNextNode(Node *nextNodePtr){
	next = nextNodePtr;
}

Enemy* Node::getItem() const {
	return pointer;
}

Node* Node::getNextPtr() const {
	return next;
}

string Node::getInfo() const {
	return pointer->GetInfo();
}
