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
	//Pile utilis�e pour le calcul du chemin de sortie
	//Le premier pas vers la sortie sera au fond de la pile
	Stack stepsToExit;
	//Pile pour la solution finale qui est la pile de calcul renvers�e
	//Le premier pas devient au sommet de la pile
	Stack reversedStepsToExit;
	//File utilis�e pour l'algorithme de r�cursivit�
	Queue allPoints;
	//Le cube re�u en construction pour solutionner les algorithmes
	Cube* cube = NULL;
	//Pile pour conserver les possibilites (blocs de d�placements possibles).
	Stack possibilities;
	//Attribut pour conserver le nombre de possibilites.
	int possibilitiesCount;
	//Methode pour compter les nodes de la pile de possibilites.
	int countPile();
	//Methodes pour verifier les possibilites de deplacements.
	bool canGoUpward(Block* currentBlock);
	bool canGoDownward(Block* currentBlock);
	bool canGoLeftward(Block* currentBlock);
	bool canGoRightward(Block* currentBlock);
	bool canGoForward(Block* currentBlock);
	bool canGoBackward(Block* currentBlock);
	bool cantGoAnywhere(Block* currentBlock);
	//Methode pour verifier la presence de points et les ajouter.
	void addPoints(Block* currentBlock);
	//Methode pour verifier l'attribut "visited" et update au besoin.
	void visiteBlock(Block* currentBlock);
	void searchForWays(Block* currentBlock);
};

