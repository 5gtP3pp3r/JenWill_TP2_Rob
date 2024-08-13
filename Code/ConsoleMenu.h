#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include "Cube.h"
#include "DataStructure.h"
#include "Rob.h"

using namespace std;
class ConsoleMenu
{
public:
	ConsoleMenu();
	~ConsoleMenu();
	void run() const;

private:
	char readValidInput(char tabValidInputs[], int nbElements) const;
	void displayMenu() const;
	void displayCredits() const;
	bool manageSelection(char entry) const;
	
	//TODO : Signature de la fonction displaySolution
};

