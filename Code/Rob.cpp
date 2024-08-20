#include "stdafx.h"
#include "Rob.h"


ROB::ROB(Cube* _cube)
{
	cube = _cube;
}


ROB::~ROB()
{

}

/// <summary>
/// Permet de trouver le chemin de sortie en utilisant la pile stepsToExit
/// </summary>
void ROB::solvePathToExit()
{
	Block* currentBlock = cube->getStartBlock();    // modifi� pour voir l'adresse du bloc ici avant de push
	stepsToExit.push(currentBlock);
	cout << endl << "push startBlock" << endl;

	while (currentBlock->value != 'E')		// Le currentBlock est updat� � la ligne 27 donc �a cause un pop avant la sortie.
	{																	// On doit aller chercher le premier sur la pile de stepsToExit et voir si la valeur est 'E'
		if (canGoUpward(currentBlock))
		{
			stepsToExit.push(currentBlock->upBlock);
			cout << "push up" << endl;							/**********  HINT isoler une variable au lieux de rechercher � chaque tour dans la condition while  *******/
		}
		else if (canGoDownward(currentBlock))
		{
			stepsToExit.push(currentBlock->downBlock);
			cout << "push down" << endl;
		}
		else if (canGoLeftward(currentBlock))
		{
			stepsToExit.push(currentBlock->leftBlock);
			cout << "push left" << endl;
		}
		else if (canGoRightward(currentBlock))
		{
			stepsToExit.push(currentBlock->rightBlock);
			cout << "push right" << endl;
		}
		else if (canGoForward(currentBlock))
		{
			stepsToExit.push(currentBlock->frontBlock);
			cout << "push front" << endl;
		}
		else if (canGoBackward(currentBlock))
		{
			stepsToExit.push(currentBlock->behindBlock);
			cout << "push back" << endl;
		}
		else
		{
			stepsToExit.pop();
			cout << "pop, back to last block" << endl;
		}
		visiteBlock(currentBlock);
		currentBlock = stepsToExit.getFirstNode()->getBlock();
	}
}

/// <summary>
/// Permet de trouver r�cursivement tous les points en utilisant la file allPoints
/// N'oubliez pas de diviser le probl�me, si le probl�me n'est pas divisible, appel
/// r�cursif est inutile et le robot courant doit continuer son exploration
/// </summary>
void ROB::solveAllPoints(Block* currentBlock)
{
	if (cantGoAnywhere(currentBlock))
	{
		return;
	}

	if (canGoUpward(currentBlock))
	{
		currentBlock = currentBlock->upBlock;		
		cout << "moved to upper block" << endl;
	}
	else if (canGoDownward(currentBlock))
	{
		currentBlock = currentBlock->downBlock;		
		cout << "moved to lower block" << endl;
	}
	addPoints(currentBlock);
	visiteBlock(currentBlock);
	
	searchForWays(currentBlock);
	possibilitiesCount = countPile();

	while (possibilitiesCount > 0)
	{
		if (possibilitiesCount == 1)
		{
			currentBlock = possibilities.pop();
			addPoints(currentBlock);
			visiteBlock(currentBlock);	
			cout << "Single posibility move" << endl;
		}
		else if (possibilitiesCount > 1)
		{
			for (int i = 0; i < possibilitiesCount; i++)
			{
				currentBlock = possibilities.pop();
				addPoints(currentBlock);
				visiteBlock(currentBlock);				
				solveAllPoints(currentBlock);
				cout << "Recursively moved to next block." << endl;
			}
		}
		searchForWays(currentBlock);
		possibilitiesCount = countPile();
	}
}

/// <summary>
/// Fonction qui permet d'obtenir la pile qui contient le chemin de sortie dans le bon ordre
/// Attention : Les pas stock�s dans stepsToExit sont � l'envers
/// il faut utiliser la pile reversedStepsToExit pour les r�organiser
/// </summary>
/// <returns> l'Adresse de la Stack contenant la solution du labyrinthe dans le bon ordre</returns>

Stack* ROB::getSolutionPathToExit()
{
	while (stepsToExit.getFirstNode() != NULL)							// Mod condition, on pige dans stepsToExit jusqu'� NULL et non dans reversedStepsToExit
	{																	// � se moment reversedStepsToExit est NULL et la condition retourne NULL
		reversedStepsToExit.push(stepsToExit.pop());
	}

	return (Stack*)&reversedStepsToExit;
}

/// <returns>l'Adresse de la Queue contenant la solution des points </returns>
Queue* ROB::getSolutionAllPoints() const
{
	return (Queue*)&allPoints;
}

int ROB::countPile()
{
	return possibilities.getNumNodes();
}
bool ROB::canGoUpward(Block* currentBlock)
{
	if (currentBlock != NULL &&
		currentBlock->value == 'U' &&
		!currentBlock->upBlock->visited)
	{
		return true;
	}
	return false;
}
bool ROB::canGoDownward(Block* currentBlock)
{
	if (currentBlock != NULL &&
		currentBlock->value == 'D' &&
		!currentBlock->downBlock->visited)
	{
		return true;
	}
	return false;
}
bool ROB::canGoLeftward(Block* currentBlock)
{
	if (currentBlock->leftBlock != NULL &&
		currentBlock->leftBlock->value != '*' &&
		!currentBlock->leftBlock->visited)
	{
		return true;
	}
	return false;
}
bool ROB::canGoRightward(Block* currentBlock)
{
	if (currentBlock->rightBlock != NULL &&
		currentBlock->rightBlock->value != '*' &&
		!currentBlock->rightBlock->visited)
	{
		return true;
	}
	return false;
}
bool ROB::canGoForward(Block* currentBlock)
{
	if (currentBlock->frontBlock != NULL &&
		currentBlock->frontBlock->value != '*' &&
		!currentBlock->frontBlock->visited)
	{
		return true;
	}
	return false;
}
bool ROB::canGoBackward(Block* currentBlock)
{
	if (currentBlock->behindBlock != NULL &&
		currentBlock->behindBlock->value != '*' &&
		!currentBlock->behindBlock->visited)
	{
		return true;
	}
	return false;
}
bool ROB::cantGoAnywhere(Block* currentBlock)
{
	if (!canGoUpward(currentBlock) &&
		!canGoDownward(currentBlock) &&
		!canGoLeftward(currentBlock) &&
		!canGoRightward(currentBlock) &&
		!canGoForward(currentBlock) &&
		!canGoBackward(currentBlock))
	{
		return true;
	}
	return false;
}
void ROB::addPoints(Block* currentBlock)
{
	if (currentBlock->points > 0 &&
		!currentBlock->visited)
	{
		allPoints.add(currentBlock);
		cout << currentBlock->points << " points added" << endl;
	}
}
void ROB::visiteBlock(Block* currentBlock)
{
	if (!currentBlock->visited)
	{
		currentBlock->visited = true;
		cout << "moved to next block (visited)" << endl;
	}
}
void ROB::searchForWays(Block* currentBlock)
{
	if (canGoUpward(currentBlock))
	{
		currentBlock = currentBlock->upBlock;
		cout << "moved to upper block" << endl;
	}
	else if (canGoDownward(currentBlock))
	{
		currentBlock = currentBlock->downBlock;
		cout << "moved to lower block" << endl;
	}
	else
	{
		if (canGoLeftward(currentBlock))
		{
			possibilities.push(currentBlock->leftBlock);
			cout << "Can move to left Block" << endl;
		}
		if (canGoRightward(currentBlock))
		{
			possibilities.push(currentBlock->rightBlock);
			cout << "Can move to right Block" << endl;
		}
		if (canGoForward(currentBlock))
		{
			possibilities.push(currentBlock->frontBlock);;
			cout << "Can move to front Block" << endl;
		}
		if (canGoBackward(currentBlock))
		{
			possibilities.push(currentBlock->behindBlock);
			cout << "Can move to Back Block" << endl;
		}
	}
}