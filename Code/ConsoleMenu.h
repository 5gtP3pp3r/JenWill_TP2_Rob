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
	~ConsoleMenu();														/*************************************************/
	void run();															/******* Optimisation, dois enlever const. *******/
																		/*************************************************/
private:
	char readValidInput(char tabValidInputs[], int nbElements) const;
	void displayMenu() const;
	void displayCredits() const;										/*******************************************************/
	bool manageSelection(char entry, Cube* cube, ROB* rob);				/******* Optimisation, utilisation de pointeurs. *******/
	//Méthode display polymorphe										/*******************************************************/
	void displaySolution(DataStructure& solution) const;
	//Destruction des blocs												/*********************************************************************/
	void blocksDestruction(Cube* cube);									/******* Optimisation, destruction des blocs dans ConsoleMenu. *******/
	//Pour le plaisir :)												/*********************************************************************/
	void displayROB(char entry) const;

};

