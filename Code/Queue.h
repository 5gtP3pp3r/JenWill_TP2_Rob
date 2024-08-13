#pragma once
#include "Node.h"
#include <string>
#include <iostream>
#include "DataStructure.h"

using namespace std;
class Queue : public DataStructure
{
	public:
		Queue();
		~Queue();
		void add(Block* block);
		Block* remove();
		void display() const override;
		Node* getLastNode() const;
	private:
		//Le dernier node de la file
		Node* lastNode;
};

