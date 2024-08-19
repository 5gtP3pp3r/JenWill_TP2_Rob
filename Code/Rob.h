#pragma once
#include "Cube.h"
#include "Stack.h"
#include "Queue.h"
#include <iostream>
#include <string>

using namespace std;

class ROB
{
public:
	ROB(Cube* _cube);
	~ROB();
	void solvePathToExit();
	void solveAllPoints(Block* startingBlock);
	Stack* getSolutionPathToExit();
	Queue* getSolutionAllPoints() const;


private:
	//Pile utilisée pour le calcul du chemin de sortie
	//Le premier pas vers la sortie sera au fond de la pile
	Stack stepsToExit;
	//Pile pour la solution finale qui est la pile de calul renversée
	//Le premier pas devient au sommet de la pile
	Stack reversedStepsToExit;
	//File utilisée pour l'algorithme de récursivité
	Queue allPoints;
	//Le cube reçu en construction pour solutionner les algorithmes
	Cube* cube = NULL;
	//Pour recursivite possibles.
	Stack possibilities;
	//Compte des possibilites
	int possibilityCount;
	//Methode pour compter les nodes de la pile de possibilites.
	int countPile();
}

