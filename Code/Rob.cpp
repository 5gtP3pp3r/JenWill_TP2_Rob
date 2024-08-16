#include "stdafx.h"
#include "Rob.h"


ROB::ROB(Cube* _cube)
{

}


ROB::~ROB()
{

}

/// <summary>
/// Permet de trouver le chemin de sortie en utilisant la pile stepsToExit
/// </summary>
void ROB::solvePathToExit()
{
	stepsToExit.push(cube->getStartBlock());
	Block* currentBlock = stepsToExit.getFirstNode()->getBlock();

	while (currentBlock->value != 'E')
	{
		if (currentBlock->upBlock->value=='U')
		{
			currentBlock->visited = true;
			stepsToExit.push(currentBlock->upBlock);
		}
		else if (currentBlock->downBlock->value=='D')
		{
			currentBlock->visited = true;
			stepsToExit.push(currentBlock->downBlock);
		}
		else if (currentBlock->leftBlock->value != '*' ||
			currentBlock->leftBlock->value != NULL &&
			!currentBlock->visited)
		{
			currentBlock->visited = true;
			stepsToExit.push(currentBlock->leftBlock);
		}
		else if (currentBlock->rightBlock->value != '*' ||
			currentBlock->rightBlock->value != NULL &&
			!currentBlock->visited)
		{
			currentBlock->visited = true;
			stepsToExit.push(currentBlock->rightBlock);
		}
		else if (currentBlock->frontBlock->value != '*' ||
			currentBlock->frontBlock->value != NULL &&
			!currentBlock->visited)
		{
			currentBlock->visited = true;
			stepsToExit.push(currentBlock->frontBlock);
		}
		else if (currentBlock->behindBlock->value != '*' ||
			currentBlock->behindBlock->value != NULL &&
			!currentBlock->visited)
		{
			currentBlock->visited = true;
			stepsToExit.push(currentBlock->behindBlock);
		}

		stepsToExit.pop();
	}
}

/// <summary>
/// Permet de trouver récursivement tous les points en utilisant la file allPoints
/// N'oubliez pas de diviser le problème, si le problème n'est pas divisible, appel
/// récursif est inutile et le robot courant doit continuer son exploration
/// </summary>
void ROB::solveAllPoints(Block* startingBlock)
{

}

/// <summary>
/// Fonction qui permet d'obtenir la pile qui contient le chemin de sortie dans le bon ordre
/// Attention : Les pas stockés dans stepsToExit sont à l'envers
/// il faut utiliser la pile reversedStepsToExit pour les réorganiser
/// </summary>
/// <returns> l'Adresse de la Stack contenant la solution du labyrinthe dans le bon ordre</returns>

Stack* ROB::getSolutionPathToExit()
{
	while (reversedStepsToExit.getFirstNode()->getBlock()->value != 'S')
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
