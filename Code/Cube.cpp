#include "stdafx.h"
#include "Cube.h"
#include "constants.h"

//TODO : Compléter cette classe


Cube::Cube(string cubePath)
{
	ifstream streamInput;
	streamInput.open(cubePath);
	string currentLine;

	Block* currentBlock = new Block;
	startBlock = NULL;

	if (streamInput)
	{
		int y = 0;
		int z = 0;
		while (getline(streamInput, currentLine))
		{
			/*int dimension = 0;
			if (currentLine != "+")                   est que cette idée a une valeur?
			{
				dimension = currentLine.length();
			}*/

			if (currentLine == "+")
			{
				z++;
				y = 0;
			}
			else
			{
				for (int x = 0; x < DIMENSION; x++)
				{
					currentBlock = tabBlocks[x][y][z];

					if (isdigit(currentLine[x])) {
						currentBlock->points = currentLine[x];
						currentBlock->value = ' ';
					}
					else {
						currentBlock->points = 0;
						currentBlock->value = currentLine[x];
					}

					currentBlock->value = currentLine[x];

					if (currentLine[x] == 'S')
					{
						startBlock = tabBlocks[x][y][z];
					}
					if (x != 0)
					{
						currentBlock->leftBlock = tabBlocks[x - 1][y][z];
						tabBlocks[x - 1][y][z]->rightBlock = currentBlock;
					}
					if (y != 0)
					{
						currentBlock->behindBlock = tabBlocks[x][y - 1][z];
						tabBlocks[x][y - 1][z]->frontBlock = currentBlock;
					}
					if (z != 0)
					{
						currentBlock->downBlock = tabBlocks[x][y][z - 1];
						tabBlocks[x][y][z - 1]->upBlock = currentBlock;
					}
				}
				y++;
			}
		}
		streamInput.close();
	}
}


Cube::~Cube()
{
	for (int z = 0; z < DIMENSION; z++)
	{
		for (int y = 0; y < DIMENSION; y++)
		{
			for (int x = 0; x < DIMENSION; x++)
			{
				delete tabBlocks[x][y][z];
			}
		}
	}
}

Block* Cube::getStartBlock()
{
	return startBlock;
}


void Cube::resetAllVisitedBlocksToFalse()
{
	for (int z = 0; z < DIMENSION; z++)
	{
		for (int y = 0; y < DIMENSION; y++)
		{
			for (int x = 0; x < DIMENSION; x++)
			{
				if (tabBlocks[x][y][z]->value != '*')
				{
					tabBlocks[x][y][z]->visited = false;
				}
			}
		}
	}
}