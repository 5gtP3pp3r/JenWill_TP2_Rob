#include "stdafx.h"
#include "DataStructure.h"

DataStructure::DataStructure() : firstNode(NULL)
{
}

DataStructure::~DataStructure()
{
}

int DataStructure::getNumNodes() const
{
	int numNodes = 0;
	Node* temp = firstNode;
	while (temp != NULL)
	{
		numNodes++;
		temp = temp->getNext();
	}

	return numNodes;
}

void DataStructure::setFirstNode(Node* node)
{
	this->firstNode = node;
}

Node* DataStructure::getFirstNode() const
{
	return this->firstNode;
}