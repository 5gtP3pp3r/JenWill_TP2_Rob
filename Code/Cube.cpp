#include "stdafx.h"
#include "Cube.h"
#include "constants.h"


//TODO : Compl�ter cette classe


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
				z++;
				y = 0;
			}

			else
			{
				for (int x = 0; x < DIMENSION; x++)
					{
						//todo : Allocation des blocs dans le tableau 3D
						//todo : Logique des cha�nages
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