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
	Block* currentBlock = cube->getStartBlock();						// Rob commence au block de départ :-).
	stepsToExit.push(currentBlock);										// Il met le block dans sa pile.
	cout << endl << "push startBlock" << endl;

	while (currentBlock->value != 'E')									// Tant que Rob n'a pas trouvé la sortie, il doit travailler.
	{										
		if (canGoUpward(currentBlock))									// Rob suit un plan de directions stricte. Quand il peut avancer, il fonce!!
		{																// Et il met le block dans sa pile.
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
		else															// Si Rob s'est trompé de chemin, il fait couler une larme
		{																// Et enlève le block de sa pile.
			stepsToExit.pop();
			cout << "pop, back to last block" << endl;
		}
		visiteBlock(currentBlock);                                      // Rob prend soin de marquer les blocks qu'il visite comme étant "visité".
		currentBlock = stepsToExit.getFirstNode()->getBlock();          // Le premier block de la pile devient celui ou est rendu Rob!
	}
}

/// <summary>
/// Permet de trouver récursivement tous les points en utilisant la file allPoints
/// N'oubliez pas de diviser le problème, si le problème n'est pas divisible, appel
/// récursif est inutile et le robot courant doit continuer son exploration
/// </summary>
void ROB::solveAllPoints(Block* currentBlock)
{
	if (cantGoAnywhere(currentBlock))									// Si un Rob n'a plus de directions disponibles, son travail est terminé.
	{
		return;
	}

	searchForWays(currentBlock);										// Rob vérifie toutes les directions pour avancer.
	possibilitiesCount = countPile();									// Ensuite on calcule le nombre de directions possibles trouvées.

	while (possibilitiesCount > 0)										// Tant que Rob a au moins une direction possibles, il doit travailler.
	{
		if (possibilitiesCount == 1)									// Si il y a seulement une direction possible, Rob va se déplacer dans 
		{																// cette direction grace à la pile et va continuer son travail.
			currentBlock = possibilities.pop();
			addPoints(currentBlock);
			visiteBlock(currentBlock);
		}
		else if (possibilitiesCount > 1)								// Si il y a plusieurs directions possibles, Rob va demander de l'aide à d'autres Rob!
		{																	
			for (int i = 0; i < possibilitiesCount; i++)
			{
				currentBlock = possibilities.pop();
				addPoints(currentBlock);
				visiteBlock(currentBlock);
				solveAllPoints(currentBlock);							// (appels récursifs).
				cout << "Recursively moved to next block." << endl;
			}
		}
		searchForWays(currentBlock);									// Rob revérifie les directions possibles. 
		possibilitiesCount = countPile();								// On recalcul le nombre de directions possibles pour continuer la boucle au besoin.
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

/// <returns>l'Adresse de la Queue contenant la solution des points. </returns>
Queue* ROB::getSolutionAllPoints() const
{
	return (Queue*)&allPoints;
}
/// <summary>
/// Retourne le nombre de directions possibles (disponibles). Utilisé dans solveAllPoints().
/// </summary>
/// <returns></returns>
int ROB::countPile()
{
	return possibilities.getNumNodes();
}
/// <summary>
/// Pour toutes les méthodes "canGo... Rob vérifie si il peut aller vers cette direction. Retourne vrai si c'est possible.
/// </summary>
/// <returns>booléen</returns>
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
/// La méthode cantGoAnywhere appelle toutes les méthodes "canGo..." par la négation.  
/// Si tout les retours sont vrai. Le retour final sera vrai "cantGoAnywhere".
/// </summary>
/// <returns> booléen, vrai "cantGoAnywhere". </returns>
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
/// <summary>
/// Rob ajoute les points trouvés dans le file.
/// </summary>
void ROB::addPoints(Block* currentBlock)
{
	if (currentBlock->points > 0 &&
		!currentBlock->visited)
	{
		allPoints.add(currentBlock);
		cout << currentBlock->points << " points added" << endl;
	}
}
/// <summary>
/// Rend le bloc actuel 'visité'. 
/// </summary>
void ROB::visiteBlock(Block* currentBlock)
{
	if (!currentBlock->visited)
	{
		currentBlock->visited = true;
		cout << "Block visited" << endl;
	}
}
/// <summary>
/// Rob vérifie toutes les directions pour trouver ceux disponibles. Si une direction est disponible, Rob le met dans sa pile.
/// </summary>
/// <param name="currentBlock"></param>
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