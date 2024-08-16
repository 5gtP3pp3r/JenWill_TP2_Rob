#include "stdafx.h"
#include "Stack.h"

Stack::Stack()
{
	
}

Stack::~Stack()
{	
	while (pop());
}

Block* Stack::pop()
{
	Block* block = NULL;
	if (this->getFirstNode() != NULL) {
		block = this->getFirstNode()->getBlock();
		Node* tempNode = this->getFirstNode();
		this->setFirstNode(this->getFirstNode()->getNext());
		delete tempNode;
	}
	return block;
}

void Stack::push(Block* block)
{
	Node* newNode = new Node();
	newNode->setBlock(block);
	newNode->setNext(this->getFirstNode());
	this->setFirstNode(newNode);
}

void Stack::display() const
{
	Node* currentNode = this->getFirstNode();
	cout << endl;
	while (currentNode != NULL) {
		cout << "[ " 
			 << currentNode->getBlock()->x << ", "  
			 << currentNode->getBlock()->y << ", " 
			 << currentNode->getBlock()->z 
			 << " ]" /* << endl*/;
		if (currentNode->getBlock()->value == 'S')
		{
			cout << " Bloc de depart";
		}
		if (currentNode->getBlock()->value == 'E')
		{
			cout << " Bloc de sortie" << endl;
		}
		cout << endl ;
		currentNode = currentNode->getNext();
	}
}