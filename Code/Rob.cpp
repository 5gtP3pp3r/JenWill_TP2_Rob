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
	Stack blockPath;
	blockPath.push(cube->getStartBlock());
	Block currentBlock;

	while (blockPath.getFirstNode()->getBlock()->value != 'E') 
	{
		
	}
}

/// <summary>
/// Permet de trouver r�cursivement tous les points en utilisant la file allPoints
/// N'oubliez pas de diviser le probl�me, si le probl�me n'est pas divisible, appel
/// r�cursif est inutile et le robot courant doit continuer son exploration
/// </summary>
void ROB::solveAllPoints(Block * startingBlock)
{
	
}

/// <summary>
/// Fonction qui permet d'obtenir la pile qui contient le chemin de sortie dans le bon ordre
/// Attention : Les pas stock�s dans stepsToExit sont � l'envers
/// il faut utiliser la pile reversedStepsToExit pour les r�organiser
/// </summary>
/// <returns> l'Adresse de la Stack contenant la solution du labyrinthe dans le bon ordre</returns>

Stack * ROB::getSolutionPathToExit()
{
	//TODO : R�organiser le chemin de sortie
	
	return (Stack*)&reversedStepsToExit;
}

/// <returns>l'Adresse de la Queue contenant la solution des points </returns>
Queue * ROB::getSolutionAllPoints() const
{
	return (Queue*)&allPoints;
}
