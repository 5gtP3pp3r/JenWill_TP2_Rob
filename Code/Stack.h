#pragma once
#include "Node.h"
#include "DataStructure.h"
#include <iostream>
#include <string>
using namespace std;

class Stack : public DataStructure
{
public:
    Stack();
    ~Stack();
    Block* pop();
    void push(Block* block);
	void display() const override;
};

