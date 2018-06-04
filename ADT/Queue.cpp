#include "Queue.h"

LinkedQueue::LinkedQueue(){
	frontPtr = nullptr;
	backPtr = nullptr;
	Size=0;
}

LinkedQueue::~LinkedQueue(){
	if (isEmpty()){
		frontPtr = backPtr = nullptr;
		return;
	}

	Node * currPtr = frontPtr;
	Node * nodeToDelete;

	while (currPtr != nullptr){
		nodeToDelete = currPtr;

		currPtr = currPtr->getNextPtr();

		delete nodeToDelete;
	}

	frontPtr = backPtr = nullptr;
	Size=0;
}

bool LinkedQueue::isEmpty() const {
	if (frontPtr ==  nullptr && backPtr == nullptr) return true;
	return false;
}

bool LinkedQueue::enqueue(Enemy *newEntry){
	Size++;

	if (isEmpty()){
		frontPtr = new Node (newEntry, nullptr);
		backPtr = frontPtr;
	}
	else {
		Node * newNode = new Node(newEntry, nullptr);
		backPtr->setNextNode(newNode);
		backPtr = newNode;
	}
	return true;
}

bool LinkedQueue::dequeue(Enemy *& PopedEntry){
	if (isEmpty()) return false;
	Size--;
	
	PopedEntry = frontPtr->getItem();

	//1 Node only in queue
	if (frontPtr == backPtr){
		delete frontPtr;
		frontPtr = backPtr = nullptr;
		return true;
	}

	Node * NodeToDelete = frontPtr;

	//shift frontPtr to the next element
	frontPtr = frontPtr->getNextPtr();

	delete NodeToDelete;
	NodeToDelete = nullptr;

	return true;

}

Enemy *LinkedQueue::peekFront() const {
	if (!isEmpty())
		return frontPtr->getItem();
	else
		return nullptr;
}
int LinkedQueue::GetSize() const
{
	return Size;
}
