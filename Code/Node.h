#pragma once
#include "Block.h"

class Node
{
	public:
		Node();
		~Node();
		void setNext(Node* _nextNode);
		Node* getNext() const;
		void setBlock(Block * _block);
		Block * getBlock() const;

	private:
		//Le prochain node
		Node* next;
		//Le bloc dans le node (c'est le contenu vu au cours)
		Block* block;
};

