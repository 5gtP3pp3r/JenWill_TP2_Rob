#include "stdafx.h"
#include "Cube.h"


//TODO : Compl�ter cette classe


Cube::Cube(string cubePath)
{
	ifstream streamInput;
	streamInput.open(cubePath);
	string currentLine;


	if (streamInput)
	{
		//TODO : Choisir une des deux strat�gies de stockage dans le fichier "options_stockage.cpp"
		//       et l'impl�menter ici
		//NOTE : Les 2 options n�cessitent la m�me quantit� de code, prenez celle qui vous inspire le plus


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