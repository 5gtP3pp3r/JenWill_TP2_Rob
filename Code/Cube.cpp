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
		int y = 0;
		int z = 0;
		while (getline(streamInput, currentLine))
		{
			if (currentLine == "+")
			{
				//todo : On change de niveau
				//todo : On replace le compteur y
			}

			else
			{
				for (//todo : Boucle du x à compléter)
					{
						//todo : Allocation des blocs dans le tableau 3D
						//todo : Logique des chaînages
					}

					//todo : on vient de traiter une ligne donc ...
			}

		}
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