#include "stdafx.h"
#include "Cube.h"


//TODO : Compléter cette classe


Cube::Cube(string cubePath)
{
	ifstream streamInput;
	streamInput.open(cubePath);
	string currentLine;


	if (streamInput)
	{
		//TODO : Choisir une des deux stratégies de stockage dans le fichier "options_stockage.cpp"
		//       et l'implémenter ici
		//NOTE : Les 2 options nécessitent la même quantité de code, prenez celle qui vous inspire le plus


		streamInput.close();
	}
}


Cube::~Cube()
{
	
}

Block* Cube::getStartBlock()
{
	return startBlock;
}


void Cube::resetAllVisitedBlocksToFalse()
{
	
}