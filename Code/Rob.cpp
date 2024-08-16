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
	Block* currentBlock = cube->getStartBlock();    // modifié pour voir l'adresse du bloc ici avant de push
	stepsToExit.push(currentBlock);
	
	while (currentBlock->value != 'E')
	{
		currentBlock = stepsToExit.getFirstNode()->getBlock();
		if (currentBlock->value == 'U')
		{
			stepsToExit.push(currentBlock->upBlock);
		}
		else if (currentBlock->value == 'D')
		{
			stepsToExit.push(currentBlock->downBlock);
		}
		else if (currentBlock->leftBlock != NULL && 
				 currentBlock->leftBlock->value != '*' &&
			    !currentBlock->leftBlock->visited)
		{
			stepsToExit.push(currentBlock->leftBlock);
		}
		else if (currentBlock->rightBlock != NULL && 
				 currentBlock->rightBlock->value != '*' &&
			    !currentBlock->rightBlock->visited)
		{
			stepsToExit.push(currentBlock->rightBlock);
		}
		else if (currentBlock->frontBlock != NULL && 
				 currentBlock->frontBlock->value != '*' &&
			    !currentBlock->frontBlock->visited)
		{
			stepsToExit.push(currentBlock->frontBlock);
		}
		else if (currentBlock->behindBlock != NULL && 
				 currentBlock->behindBlock->value != '*' &&
			    !currentBlock->behindBlock->visited)
		{
			stepsToExit.push(currentBlock->behindBlock);
		}
		else 
		{
			currentBlock->visited = true;
			stepsToExit.pop();
		}		
	}
}

/// <summary>
/// Permet de trouver récursivement tous les points en utilisant la file allPoints
/// N'oubliez pas de diviser le problème, si le problème n'est pas divisible, appel
/// récursif est inutile et le robot courant doit continuer son exploration
/// </summary>
void ROB::solveAllPoints(Block* startingBlock)
{
	/************************************     À COMPLÉTER     **********************************/
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
