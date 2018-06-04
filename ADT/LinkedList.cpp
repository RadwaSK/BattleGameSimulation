#pragma once
#include "LinkedList.h"
#include<fstream>
#include<iostream>

ofstream & operator << (ofstream& out,Enemy* ptr)
{
	Enemy::IncrementSeq();
	out<<to_string(ptr->getKTS())+"\t"+to_string(Enemy::getSequence())+"\t"+to_string(ptr->getFD())+"\t"+to_string(ptr->getKD())+"\t"+to_string(ptr->getLT())+"\n";
	return out;
}

//*************** Utility Functions **************
void LinkedList::MergeSort(){
	Node * curr = head;
	int size = 0;

	while (curr){
		size++;
		curr = curr->getNextPtr();
	}
	if (size == 1)
		return;

	Enemy ** list = new Enemy*[size];
	int index = 0;

	curr = head;

	while (curr){
		list[index++] = curr->getItem();
		curr = curr->getNextPtr();
	}

	clear();
	MergeSortRec(list, size);
	
	index = 0;
	for (int i = 0; i<size; i++)
		add(list[i]);

	delete [] list;
}

void LinkedList::MergeSortRec(Enemy ** lst, int size){
	if (size == 2){
		if (*lst[1] > *lst[0]){
			Enemy* temp = lst[0];
			lst[0] = lst[1];
			lst[1] = temp;
		}
		return;
	}


	int sz1 = size/2;
	int sz2 = size - sz1;

	Enemy **arr1 = new Enemy*[sz1];
	Enemy **arr2 = new Enemy*[sz2];

	for (int i = 0; i<sz1; i++){
		arr1[i] = lst[i];
		arr2[i] = lst[i+sz1];
	}
	if (sz2 != sz1) arr2[sz2-1] = lst[size-1];

	if (sz1 != 1)	MergeSortRec(arr1, sz1);
	if (sz2 != 1)	MergeSortRec(arr2, sz2);

	int counter2 = 0, counterLST = 0, counter1 = 0;

	for (; counter1<sz1 && counter2<sz2; ){

		if (*arr1[counter1] > *arr2[counter2])
			lst[counterLST++] = arr1[counter1++];
		else
			lst[counterLST++] = arr2[counter2++];


	}

	for (; counter1<sz1; counter1++, counterLST++)
		lst[counterLST] = arr1[counter1];

	for (; counter2<sz2; counter2++, counterLST++)
		lst[counterLST] = arr2[counter2];

	delete [] arr1, arr2;
}

//*************** Public Functions **************

//Default constructor
LinkedList::LinkedList(){
	head = tail = nullptr;
}

// Copy constructor
LinkedList::LinkedList(const LinkedList& aList){ 
	if (aList.isEmpty()){
		head = tail = nullptr;
		return;
	}

	head = new Node(aList.head->getItem());
	if (aList.head->getNextPtr() == nullptr){
		head->setNextNode(nullptr);
		tail = head;
		return;
	}

	Node* currPtr = head;
	Node* aListCurrPtr = aList.head->getNextPtr();
	Node* newNode;
	while (aListCurrPtr != nullptr){
		newNode = new Node(*aListCurrPtr);
		currPtr->setNextNode(newNode);
		currPtr = newNode;
		aListCurrPtr = aListCurrPtr->getNextPtr();
	}
	tail = newNode;
	newNode->setNextNode(nullptr);
}

//Check if empty
bool LinkedList::isEmpty() const {
	if (head == nullptr)
		return true;
	return false;
}

//Add an item
void LinkedList::add(Enemy * newEntry){
	//means was empty
	if (isEmpty()){
		Node* newNode = new Node(newEntry, nullptr);
		head = tail = newNode;
		return;
	}

	//else, add in end
	Node *newNode = new Node(newEntry, nullptr);
	tail->setNextNode(newNode);
	tail = newNode;
}

//remove an enemy
bool LinkedList::remove(Enemy * anEntry){
	Node * prev;
	Node* ptr = getPointerTo(anEntry, prev);

	//if not found
	if (ptr == nullptr)
		return false;

	//if target is head
	if (prev == nullptr){
		Node * nodeToDelete = head;
		if (head == tail)		//if 1 element only in list
			tail = tail->getNextPtr();
		head = head->getNextPtr();
		delete nodeToDelete;
		nodeToDelete = nullptr;
		return true;
	}

	prev->setNextNode(ptr->getNextPtr());
	delete ptr;
	ptr = nullptr;

	return true;
}

//clear list and delete all enemies
void LinkedList::clear(){
	if (isEmpty()) return;

	Node* nodeToDeletePtr;

	while (head != nullptr)
	{
		nodeToDeletePtr = head;
		head = head->getNextPtr();

		// Return node to the system
		nodeToDeletePtr->setNextNode(nullptr);
		delete nodeToDeletePtr;
	} // end while

	// headPtr is nullptr
	nodeToDeletePtr = nullptr ;
	head = tail = nullptr;
}


//Clears the linked list AND Deallocate the pointers stored in nodes
void LinkedList::clearAndDelete() {
	if (isEmpty()) return;

	Node* nodeToDeletePtr;
	Enemy * PtrToDeallocate;

	while (head != nullptr)
	{
		nodeToDeletePtr = head;
		PtrToDeallocate = nodeToDeletePtr->getItem();
		head = head->getNextPtr();

		// Return node to the system
		nodeToDeletePtr->setNextNode(nullptr);
		delete PtrToDeallocate;	//delete the ptr
		delete nodeToDeletePtr;	//delete the node
	} // end while

	// headPtr is nullptr
	nodeToDeletePtr = nullptr ;
	head = tail = nullptr;

	PtrToDeallocate = nullptr;
}

//check if an Enemy exists
bool LinkedList::contains(Enemy* anEntry) const {
	Node * dummy;
	return getPointerTo(anEntry, dummy) != nullptr;
}

//getItem that points to target enemy
Node* LinkedList::getPointerTo(Enemy * target, Node *& prev) const {
	prev = nullptr;

	//if empty
	if (isEmpty())
		return nullptr;

	if (head->getItem() == target)
		return head;

	Node* currentPtr = head->getNextPtr();
	prev = head;

	while (currentPtr != nullptr){
		if (currentPtr->getItem() == target)
			return currentPtr;

		prev = currentPtr;
		currentPtr = currentPtr->getNextPtr();
	}
	return nullptr;
}

//sort LinkedList according to priorities descendingly
void LinkedList::sort(){
	MergeSort();
}

//Destructor
LinkedList::~LinkedList(){
	clear();
}

void LinkedList::PrintAndClear(ofstream & out ) {
	if (isEmpty())
		return;
	
	sort();
	
	Node* Temp=head;
	while(Temp!=nullptr)
	{
		out<<Temp->getItem();
		Temp=Temp->getNextPtr();

	}
	clear();
}

void LinkedList::TraverseHeadFirst(void visit(Enemy *), int n){
	if (isEmpty() || n < 1) return;
	int i = 0;
	Node * currPtr = head;

	while (currPtr && i < n){
		visit(currPtr->getItem());
		currPtr = currPtr->getNextPtr();
		i++;
	}
}


bool LinkedList::appendLinkedLists(LinkedList *l2){
	//if l2 is empty
	if (l2->head == nullptr)
		return false;

	//if this list is empty
	if (head == nullptr){
		head = l2->head;
	}
	else{
		tail->setNextNode(l2->head);
	}

	tail = l2->tail;
	sort();
	l2->head = l2->tail = nullptr;
	return true;
}