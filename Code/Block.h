#pragma once


struct Block
{
    int x;
    int y;
	int z;
	int points;
    char value;	

	//pour savoir s'il a �t� explor�
    bool visited = false; 
	
	Block* upBlock = nullptr;				// z + 1
	Block* downBlock = nullptr;				// z - 1
	Block* leftBlock = nullptr;				// x - 1
	Block* frontBlock = nullptr;			// y + 1
	Block* rightBlock = nullptr;			// x + 1
	Block* behindBlock = nullptr;			// y - 1
	

	//Aide-m�moire : ces pointeurs repr�sentent la priorit� pour inspecter le labyrinthe
	//1. On regarde d'abord si on peut monter de niveau
	//2. Sinon si on peut descendre de niveau
	//3. Sinon si on peut tourner � gauche
	//4. Sinon si on peut aller tout droit
	//5. Sinon si on peut tourner � droite
	//6. Sinon si on peut aller vers le bas
	
	//7. Sinon c'est un cul-de-sac, on fait marche arri�re pour tenter trouver un autre chemin

};