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
		int z = -1;														// Le fichier commence par un "+" ce qui fok le premier incrément de "z" à la ligne 25
		while (getline(streamInput, currentLine))
		{
			if (currentLine == "+")
			{
				z++;
				y = 0;
			}
			else
			{
				cout << endl;
				for (int x = 0; x < DIMENSION; x++)
				{
					tabBlocks[x][y][z] = new Block;						// Instanciation de tout les blocs à chaque index et non une seule fois.. oups lol
					cout << "Tab position: [" << x << ", " << y << ", " << z << "]" << endl;
					cout << "Tab address: \"" << *(&tabBlocks[x][y][z]) << "\"" << endl;
					currentBlock = tabBlocks[x][y][z];					// Attribution d'adresse et non des valeurs x, y, z     encore oups
					currentBlock->x = x;								// Attribution des valeurs x, y, z
					currentBlock->y = y;
					currentBlock->z = z;
					cout << "Block coordinates: [ " << currentBlock->x << ", " << currentBlock->y << ", " << currentBlock->z << " ]" << endl;
					cout << "Block address: \"" << *(&currentBlock) << "\"" << endl ;

					if (isdigit(currentLine[x])) {
						currentBlock->points = currentLine[x] - '0';	// Remarqué qu'on doit additionner des int plus tard, transfert du char du .txt en int  
						currentBlock->value = ' ';
					}
					else {
						currentBlock->points = 0;
						currentBlock->value = currentLine[x];
					}
					cout << "Block value: (" << currentBlock->value << ") Block points: (" << currentBlock->points << ")" << endl << endl;
					// currentBlock->value = currentLine[x];   en trop

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
	cout << endl << "Start Block coordinates: [ " << startBlock->x << ", " << startBlock->y << ", " << startBlock->z << " ]" << endl;
	cout << "Start Block value: (" << startBlock->value << ") Start Block points: (" << startBlock->points << ")" << endl;
	cout << "Start Block address: \"" << *(&startBlock) << "\"" << endl;
}		/********** On a un trouble de retour null à la méthode getStartBlock(). Ajout de plein de cout pour confirmer les index valeurs des attributs et adresses **********/
		/******* Les affichage montre bien que les adresses et que les transferts d'adresses entre les positions du tableau, des blocks et même de startBlock suivent *******/
		/******* Le problème doit venir au moment d'appeler la méthode getStartBlock() dans Rob et sont utilisation au autre *******/

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