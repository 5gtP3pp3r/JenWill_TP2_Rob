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
	Block* currentBlock = cube->getStartBlock();
	stepsToExit.push(currentBlock);
	cout << endl << "push startBlock" << endl;

	while (currentBlock->value != 'E')
	{
		if (canGoUpward(currentBlock))
		{
			stepsToExit.push(currentBlock->upBlock);
			cout << "push up" << endl;
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
/// Permet de trouver récursivement tous les points en utilisant la file allPoints
/// N'oubliez pas de diviser le problème, si le problème n'est pas divisible, appel
/// récursif est inutile et le robot courant doit continuer son exploration
/// </summary>
void ROB::solveAllPoints(Block* currentBlock)
{
	// Si un Rob n'a plus de directions disponibles, son travail est termine.
	// 
	if (cantGoAnywhere(currentBlock))
	{
		return;
	}

	searchForWays(currentBlock);
	possibilitiesCount = countPile();

	while (possibilitiesCount > 0)
	{
		if (possibilitiesCount == 1)
		{
			currentBlock = possibilities.pop();
			addPoints(currentBlock);
			visiteBlock(currentBlock);
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
/// Attention : Les pas stockés dans stepsToExit sont à l'envers
/// il faut utiliser la pile reversedStepsToExit pour les réorganiser
/// </summary>
/// <returns> l'Adresse de la Stack contenant la solution du labyrinthe dans le bon ordre</returns>

Stack* ROB::getSolutionPathToExit()
{
	while (stepsToExit.getFirstNode() != NULL)
	{
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

/// <summary>
/// La méthode cantGoAnywhere appelle toutes les méthodes "canGo" par la négation.  
/// Si tout les retours sont vrai. Le retour final sera vrai "cantGoAnywhere".
/// </summary>
/// <returns> booléen, vrai "cantGoAnywhere"</returns>
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
		cout << "Block visited" << endl;
	}
}

void ROB::searchForWays(Block* currentBlock)
{
	if (canGoUpward(currentBlock))
	{
		currentBlock = currentBlock->upBlock;
		cout << "Can move to upper block" << endl;
	}
	if (canGoDownward(currentBlock))
	{
		currentBlock = currentBlock->downBlock;
		cout << "Can move to lower block" << endl;
	}
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