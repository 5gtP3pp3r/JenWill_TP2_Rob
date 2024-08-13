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
	//Le bloc de d�part (utile pour la r�cursivit�)
	Block* startBlock;
	//Tableau statique de tous les blocs
	Block* tabBlocks[DIMENSION][DIMENSION][DIMENSION];
};

