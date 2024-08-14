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
	while (currentNode != NULL) {
		currentNode->getBlock()->display();     // À mettre à jour plus tard    le display sera polimorphe pour l'affichage du stack et queue
		currentNode = currentNode->getNext();
	}
}