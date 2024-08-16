#include "stdafx.h"
#include "Cube.h"
#include "constants.h"

//TODO : Compléter cette classe


Cube::Cube(string cubePath)
{
	ifstream streamInput;
	streamInput.open(cubePath);
	string currentLine;

	Block* currentBlock = NULL;
	startBlock = NULL;

	if (streamInput)
	{
		int y = 0;
		int z = -1;
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
					tabBlocks[x][y][z] = new Block;
					currentBlock = tabBlocks[x][y][z];
					currentBlock->x = x;
					currentBlock->y = y;
					currentBlock->z = z;

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
						startBlock = currentBlock;
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
				if (tabBlocks[x][y][z]->visited == true)
				{
					tabBlocks[x][y][z]->visited = false;
				}
			}
		}
	}
}