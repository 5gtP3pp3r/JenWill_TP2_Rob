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
	
	while (stepsToExit.getFirstNode()->getBlock()->value != 'E')		// Le currentBlock est updat� � la ligne 27 donc �a cause un pop avant la sortie.
	{																	// On doit aller chercher le premier sur la pile de stepsToExit et voir si la valeur est 'E'
		currentBlock = stepsToExit.getFirstNode()->getBlock();
		if (currentBlock->value == 'U')
		{
			stepsToExit.push(currentBlock->upBlock);
			cout << "push up" << endl;
		}
		else if (currentBlock->value == 'D')
		{
			stepsToExit.push(currentBlock->downBlock);
			cout << "push down" << endl;
		}
		else if (currentBlock->leftBlock != NULL && 
				 currentBlock->leftBlock->value != '*' &&
			    !currentBlock->leftBlock->visited)
		{
			stepsToExit.push(currentBlock->leftBlock);
			cout << "push left" << endl;
		}
		else if (currentBlock->rightBlock != NULL && 
				 currentBlock->rightBlock->value != '*' &&
			    !currentBlock->rightBlock->visited)
		{
			stepsToExit.push(currentBlock->rightBlock);
			cout << "push right" << endl;
		}
		else if (currentBlock->frontBlock != NULL && 
				 currentBlock->frontBlock->value != '*' &&
			    !currentBlock->frontBlock->visited)
		{
			stepsToExit.push(currentBlock->frontBlock);
			cout << "push front" << endl;
		}
		else if (currentBlock->behindBlock != NULL && 
				 currentBlock->behindBlock->value != '*' &&
			    !currentBlock->behindBlock->visited)
		{
			stepsToExit.push(currentBlock->behindBlock);
			cout << "push back" << endl;
		}
		else 
		{			
			stepsToExit.pop();
			cout << "pop, back to last block" << endl;
		}
		currentBlock->visited = true;
	}
}

/// <summary>
/// Permet de trouver r�cursivement tous les points en utilisant la file allPoints
/// N'oubliez pas de diviser le probl�me, si le probl�me n'est pas divisible, appel
/// r�cursif est inutile et le robot courant doit continuer son exploration
/// </summary>
void ROB::solveAllPoints(Block* startingBlock)
{
	/************************************     � COMPL�TER     **********************************/
}

/// <summary>
/// Fonction qui permet d'obtenir la pile qui contient le chemin de sortie dans le bon ordre
/// Attention : Les pas stock�s dans stepsToExit sont � l'envers
/// il faut utiliser la pile reversedStepsToExit pour les r�organiser
/// </summary>
/// <returns> l'Adresse de la Stack contenant la solution du labyrinthe dans le bon ordre</returns>

Stack* ROB::getSolutionPathToExit()
{
	while (stepsToExit.getFirstNode()->getBlock()->value != 'S')		// Mod condition, on pige dans stepsToExit jusqu'� la valeur 'S' et non dans reversedStepsToExit
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
