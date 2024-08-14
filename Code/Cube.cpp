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

					if (isdigit(currentLine[x])) {
						block->points = currentLine[x];
						block->value = ' ';
					}
					else {
						block->points = 0;
						block->value = currentLine[x];
					}
					block->value = currentLine[x];
					if (currentLine[x] == 'S')
					{
						startBlock = tabBlocks[x][y][z];
					}

					if (x != 0)
					{
						block->leftBlock = tabBlocks[x - 1][y][z];
						tabBlocks[x - 1][y][z]->rightBlock = block;
					}
					if (y != 0)
					{
						block->behindBlock = tabBlocks[x][y - 1][z];
						tabBlocks[x][y - 1][z]->frontBlock = block;
					}
					if (z != 0)
					{
						block->downBlock = tabBlocks[x][y][z - 1];
						tabBlocks[x][y][z - 1]->upBlock = block;
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

}

Block* Cube::getStartBlock()
{
	return startBlock;
}


void Cube::resetAllVisitedBlocksToFalse()
{

}