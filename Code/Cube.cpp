#include "stdafx.h"
#include "Cube.h"
#include "constants.h"


//TODO : Compléter cette classe


Cube::Cube(string cubePath)
{
	ifstream streamInput;
	streamInput.open(cubePath);
	string currentLine;

	startBlock = tabBlocks[0][0][0];
	startBlock->x = 0;
	startBlock->y = 0;
	startBlock->z = 0;

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
					Block* block = NULL;
					block = tabBlocks[x][y][z];
					block->x = x;
					block->y = y;
					block->z = z;
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