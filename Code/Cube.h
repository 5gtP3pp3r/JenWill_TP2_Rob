#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include "Block.h"
#include "constants.h"
using namespace std;

class Cube
{
public:
	Cube(string cubePath);
    ~Cube();	
    Block* getStartBlock();
	void resetAllVisitedBlocksToFalse();
private:
	//Le bloc de départ (utile pour la récursivité)
	Block* startBlock;
	//Tableau statique de tous les blocs
	Block* tabBlocks[DIMENSION][DIMENSION][DIMENSION];
	//Initialisation de currentBlock et ses valeurs x, y, z.
	Block* initCurrentBlock(Block* currentBlock, int x, int y, int z);
	//Initialisation des "value" et "points" de currentBlock.
	void initBlockValuesAndPoints(Block* currentBlock, string currentLine, int x);
	void initStartBlock(Block* currentBlock, string currentLine, int x);
	//Chaines les blocs entre eux sur tout les axes en une itération.
	void chainLinkBlocks(Block* currentBlock, int x, int y, int z);
};

