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
	void run();															
																		
private:
	char readValidInput(char tabValidInputs[], int nbElements) const;
	void displayMenu() const;
	void displayCredits() const;	

	//Initialisations des cube et rob.
	void InitCubeAndRob();

	//M�thode de choix des s�lections.
	bool manageSelection(char entry);				
	//M�thode display polymorphe										
	void displaySolution(DataStructure& solution) const;
								
	//Pour le plaisir :)												
	void displayROB(char entry) const;

	// Nouveaux attributs:
	Cube* cube = nullptr;
	ROB* rob = nullptr;
};

