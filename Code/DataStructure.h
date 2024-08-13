#pragma once
#include "Node.h"
#include <string>
using namespace std;
class DataStructure
{
	public:
		DataStructure();
		~DataStructure();
		virtual void display() const = 0;
		int getNumNodes() const;
		Node* getFirstNode() const;
	protected:
		void setFirstNode(Node* node);
	private:
		//Le premier node de la structure
		Node* firstNode;
};

