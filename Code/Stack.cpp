#include "stdafx.h"
#include "Stack.h"

//TODO : Amenez le code de votre pile
//TODO : Codez le display selon les spécifications d'affichage
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
	cout << endl << "Chemin des blocks vers la sortie:" << endl;
	while (currentNode != NULL) {
		cout << "[ " 
			 << currentNode->getBlock()->x << ", " 
			 << currentNode->getBlock()->y << ", " 
			 << currentNode->getBlock()->z 
			 << " ]" << endl;                                
		currentNode = currentNode->getNext();
	}
}