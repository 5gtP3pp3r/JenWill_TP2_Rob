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
	cout << endl << "push startBlock" << endl;

	while (stepsToExit.getFirstNode()->getBlock()->value != 'E')		// Le currentBlock est updaté à la ligne 27 donc ça cause un pop avant la sortie.
	{																	// On doit aller chercher le premier sur la pile de stepsToExit et voir si la valeur est 'E'
		currentBlock = stepsToExit.getFirstNode()->getBlock();
		if (currentBlock->value == 'U')
		{
			stepsToExit.push(currentBlock->upBlock);
			cout << "push up" << endl;							/**********  HINT isoler une variable au lieux de rechercher à chaque tour dans la condition while  *******/
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
/// Permet de trouver récursivement tous les points en utilisant la file allPoints
/// N'oubliez pas de diviser le problème, si le problème n'est pas divisible, appel
/// récursif est inutile et le robot courant doit continuer son exploration
/// </summary>
void ROB::solveAllPoints(Block* currentBlock)
{
	currentBlock->visited = true;
	Block* nextBlock = NULL;

	if ((currentBlock->value != 'U' || currentBlock->value != 'D') &&
		(currentBlock->leftBlock == NULL || currentBlock->leftBlock->value == '*' || currentBlock->leftBlock->visited) &&
		(currentBlock->rightBlock == NULL || currentBlock->rightBlock->value == '*' || currentBlock->rightBlock->visited) &&
		(currentBlock->frontBlock == NULL || currentBlock->frontBlock->value == '*' || currentBlock->frontBlock->visited) &&
		(currentBlock->behindBlock == NULL || currentBlock->behindBlock->value == '*' || currentBlock->behindBlock->visited))
	{
		return;
	}

	int possibilitiesCount = 1;

	while (possibilitiesCount == 1)
	{

		if (currentBlock->points > 0)
		{
			allPoints.add(currentBlock);
			cout << "points added" << endl;
		}

		if (currentBlock->value == 'U')
		{
			currentBlock = currentBlock->upBlock;
			cout << "moved to upper block" << endl;
		}
		else if (currentBlock->value == 'D')
		{
			currentBlock = currentBlock->downBlock;
			cout << "moved to lower block" << endl;
		}
		currentBlock->visited = true;

		if (currentBlock->points > 0)
		{
			allPoints.add(currentBlock);
			cout << "points added" << endl;
		}

		if (
			currentBlock->leftBlock != NULL &&
			currentBlock->leftBlock->value != '*' &&
			!currentBlock->leftBlock->visited) {
			possibilities.push(currentBlock->leftBlock);
		}
		if (currentBlock->rightBlock != NULL &&
			currentBlock->rightBlock->value != '*' &&
			!currentBlock->rightBlock->visited) {
			possibilities.push(currentBlock->rightBlock);
		}
		if (currentBlock->frontBlock != NULL &&
			currentBlock->frontBlock->value != '*' &&
			!currentBlock->frontBlock->visited) {
			possibilities.push(currentBlock->frontBlock);
		}
		if (currentBlock->behindBlock != NULL &&
			currentBlock->behindBlock->value != '*' &&
			!currentBlock->behindBlock->visited) {
			possibilities.push(currentBlock->behindBlock);
		}

			possibilitiesCount = countPile();

		if (possibilitiesCount == 1)
		{
			nextBlock = possibilities.pop();
			currentBlock = nextBlock;
			nextBlock->visited = true;
			cout << "moved to adjacent block" << endl;

			if (nextBlock->points > 0)
			{
				allPoints.add(currentBlock);
				cout << "points added" << endl;
			}

		}
		else if (possibilitiesCount > 1)
		{	
			for (int i = 0; i < countPile(); i++) 
			{
				currentBlock = nextBlock;
				nextBlock = possibilities.pop();
				solveAllPoints(nextBlock);
				cout << "moved to adjacent block" << endl;
			}
		}
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
	while (stepsToExit.getFirstNode() != NULL)							// Mod condition, on pige dans stepsToExit jusqu'à NULL et non dans reversedStepsToExit
	{																	// À se moment reversedStepsToExit est NULL et la condition retourne NULL
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