#include "stdafx.h"
#include "Node.h"


Node::Node()
{
}

Node::~Node()
{
}

void Node::setNext(Node* _nextNode)
{
	next = _nextNode;
}

Node* Node::getNext() const
{
	return next;
}

void Node::setBlock(Block * _block)
{
	block = _block;
}

Block * Node::getBlock() const
{
	return block;
}
