#pragma once
#include "Node.h"

class LinkedList
{
	Node * head;
	Node * tail;

	// Returns either a pointer to the node containing a given entry
	// or the null pointer if the entry is not in the List.
	Node* getPointerTo (Enemy * target, Node *& prev) const ;
	
	void MergeSort();
	void MergeSortRec(Enemy ** list, int size);
public:
	LinkedList();

	LinkedList(const LinkedList & aList); // Copy constructor

	virtual ~LinkedList(); // Destructor should be virtual

	//check if it's empty
	bool isEmpty() const ;

	//add a node
	void add(Enemy *newEntry);

	//remove a node
	bool remove(Enemy * anEntry);

	//delete all nodes
	void clear();

	//Clears the linked list AND Deallocate the pointers stored in nodes
	void clearAndDelete() ;

	//check if it contains an element
	bool contains(Enemy * anEntry) const ;

	//sort according to priority
	void sort();
	
	//Print the Linked List in Output file sorted, then clears the list
	void PrintAndClear(ofstream&) ;

	//Traverse nodes in LinkedList starting from Head
	void TraverseHeadFirst(void visit(Enemy *), int n);

	//Appends two lists to each other
	//called when we append an Enemy list to another when a tower is destroyed
	bool appendLinkedLists(LinkedList *l2);
};
