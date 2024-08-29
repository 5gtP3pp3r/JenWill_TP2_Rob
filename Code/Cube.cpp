#include "stdafx.h"
#include "Cube.h"
#include "constants.h"

//TODO : Compl�ter cette classe


Cube::Cube(string cubePath)
{
	ifstream streamInput;
	streamInput.open(cubePath);
	string currentLine;

	Block* currentBlock = nullptr;										// Initialisation � NULL pour �viter du "garbage".
	startBlock = nullptr;

	if (streamInput)
	{
		int y = DIMENSION - 1;											// Placer "y" en haut des lignes pour le d�cr�menter et avoir l'axe Y dans le m�me sense que les .txt.
		int z = -1;														// Le fichier .txt commence par un "+" ce qui nuit au premier incr�ment de "z" � la ligne 25.
		while (getline(streamInput, currentLine))
		{
			if (currentLine == "+")
			{
				z++;													// Incr�mentation de "z" pour changer de niveau dans le cube.
				y = DIMENSION -1;										// R�initialisation de "y" � la premi�re valeur au changement de niveau.
			}
			else
			{
				cout << endl;
				for (int x = 0; x < DIMENSION; x++)
				{
					tabBlocks[x][y][z] = new Block;						// Instanciation de tout les blocs � chaque index.

					cout << "Tab position: [" << x << ", " << y << ", " << z << "]" << endl;
					cout << "Tab address: \"" << *(&tabBlocks[x][y][z]) << "\"" << endl;
					
					currentBlock = initCurrentBlock(currentBlock, x, y, z);

					cout << "Block coordinates: [ " << currentBlock->x << ", " << currentBlock->y << ", " << currentBlock->z << " ]" << endl;
					cout << "Block address: \"" << *(&currentBlock) << "\"" << endl ;

					initBlockValuesAndPoints(currentBlock, currentLine, x);
					initStartBlock(currentBlock, currentLine, x);					
					chainLinkBlocks(currentBlock, x, y, z);
				}
				y--;													// D�cr�mentation de "y" puisqu'on construit le cube de haut en bas.
			}
		}
		streamInput.close();
	}
	cout << endl << "Start Block coordinates: [ " << startBlock->x << ", " << startBlock->y << ", " << startBlock->z << " ]" << endl;
	cout << "Start Block value: (" << startBlock->value << ") Start Block points: (" << startBlock->points << ")" << endl;
	cout << "Start Block address: \"" << *(&startBlock) << "\"" << endl << endl;
}

Cube::~Cube()
{																		/*********************************************************************/
	for (int z = 0; z < DIMENSION; z++)
	{
		for (int y = 0; y < DIMENSION; y++)
		{
			for (int x = 0; x < DIMENSION; x++)
			{
				delete tabBlocks[x][y][z];	                   // It�ration dans le cube (statique) pour d�truire les blocs (dynamique) ;-).
			}
		}
	}
	cout << endl << "***** All blocks destroyed. *****" << endl;
}

/// <summary>
/// Retourne le bloc "startBlock"
/// </summary>
Block* Cube::getStartBlock()
{
	return startBlock;
}

/// <summary>
/// Remet la valeur de "visited" de tout les blocs visit� � "false".
/// </summary>
void Cube::resetAllVisitedBlocksToFalse()
{																		/***********************************************************/
	for (int z = 0; z < DIMENSION; z++)									/******* Optimisation, la m�thode devient essentiel. *******/
	{																	/***********************************************************/
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

/// <summary>
/// Initialisation du bloc avec le nom currentBlock qui sera utilis� tout au long du constructeur.
/// </summary>
/// <returns></returns>
Block* Cube::initCurrentBlock(Block* currentBlock, int x, int y, int z)
{
	currentBlock = tabBlocks[x][y][z];									// Attribution d'adresse.
	currentBlock->x = x;												// Attribution des valeurs x, y, z.
	currentBlock->y = y;
	currentBlock->z = z;

	return currentBlock;
}

/// <summary>
/// Initialisation des attributs "points" et "value" avec les caract�res 
/// trouv�s avec "currentLine[x] du fichier .txt fournie.
/// </summary>
void Cube::initBlockValuesAndPoints(Block* currentBlock, string currentLine, int x)
{
	if (isdigit(currentLine[x])) {
		currentBlock->points = currentLine[x] - '0';					// Conversion rapide du char du .txt en int.  
		currentBlock->value = ' ';
	}
	else {
		currentBlock->points = 0;										// Si il n'y a pas de "points" sur le bloc, nous avons d�cid� d'initialiser cette attribut 
		currentBlock->value = currentLine[x];							// � "0". Cette d�cision rend la condition plus facile pour la m�thode ROB::addPoints() :-).
	}
	cout << "Block value: (" << currentBlock->value << ") Block points: (" << currentBlock->points << ")" << endl << endl;
}

/// <summary>
/// Initialisation de StartBlock lorsqu'un bloc a l'attribut "value" = 'S'.
/// </summary>
void Cube::initStartBlock(Block* currentBlock, string currentLine, int x)
{
	if (currentLine[x] == 'S')
	{
		startBlock = currentBlock;
	}
}

/// <summary>
/// Chainage des blocs entre eux sur les 6 axes en une it�ration.
/// </summary>
void Cube::chainLinkBlocks(Block* currentBlock, int x, int y, int z)
{
	if (x > 0)															// On ne peut pas chainer avec le bloc pr�c�dent si on est � "0" sur les axes.
	{
		currentBlock->leftBlock = tabBlocks[x - 1][y][z];				// Lorsqu'on est sur un bloc, on peut chainer avec le bloc pr�c�dent.
		tabBlocks[x - 1][y][z]->rightBlock = currentBlock;				// On ne peut pas chainer avec le suivant (n'existe pas), mais on peut
	}																	// demander au pr�c�dent de se chainer avec le bloc courant.
	if (y < DIMENSION - 1)
	{
		currentBlock->frontBlock = tabBlocks[x][y + 1][z];				// M�me commentaire pour tous les axes.
		tabBlocks[x][y + 1][z]->behindBlock = currentBlock;
	}
	if (z > 0)
	{
		currentBlock->downBlock = tabBlocks[x][y][z - 1];
		tabBlocks[x][y][z - 1]->upBlock = currentBlock;
	}
}