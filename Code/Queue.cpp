#include "stdafx.h"
#include "Queue.h"
#include <iostream>
#include <chrono>
#include <thread>

Queue::Queue()
{
	
}

Queue::~Queue()
{
	while (remove());
}

Node* Queue::getLastNode() const
{
	return this->lastNode;
}

void Queue::add(Block* block)
{
	Node* newNode = new Node;
	newNode->setNext(NULL);
	newNode->setBlock(block);
	if (this->lastNode == NULL)
	{
		this->setFirstNode(newNode);
	}
	else
	{
		this->lastNode->setNext(newNode);
	}
	this->lastNode = newNode;
}

Block* Queue::remove()
{
	if (this->getFirstNode() == NULL)
	{
		return NULL;
	}
	Node* currentNode = this->getFirstNode();
	setFirstNode(currentNode->getNext());
	if (this->getFirstNode() == NULL)
	{
		this->lastNode = NULL;
	}
	Block* currentBlock = currentNode->getBlock();
	delete currentNode;
	return currentBlock;
}

void Queue::display() const
{
	Node* currentNode = getFirstNode();
	int total = 0;
	cout << endl;
	while (currentNode != NULL)
	{														
		cout << currentNode->getBlock()->points 
			 << " points dans le bloc " << "[ " 
			 << currentNode->getBlock()->x << ", "
			 << currentNode->getBlock()->y << ", " 
			 << currentNode->getBlock()->z << " ]" << endl;

		total += currentNode->getBlock()->points;
		currentNode = currentNode->getNext();
	}
	cout << "Pour un total de " << total << " points." << endl << endl;
}					