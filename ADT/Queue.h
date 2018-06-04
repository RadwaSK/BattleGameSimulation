#ifndef _LINKED_QUEUE
#define _LINKED_QUEUE

#include "Node.h"

class LinkedQueue
{
	// The queue is implemented as a chain of linked nodes that has
	// two external pointers, a head pointer for the front of the queue
	// and a tail pointer for the back of the queue.
	Node* backPtr;
	Node* frontPtr;
	int Size;

public :

	LinkedQueue();

	~LinkedQueue();

	bool isEmpty() const ;

	bool enqueue(Enemy *newEntry);

	bool dequeue(Enemy *& PopedEntry);
	int GetSize() const;

	Enemy *peekFront() const;
}; // end LinkedQueue

#endif