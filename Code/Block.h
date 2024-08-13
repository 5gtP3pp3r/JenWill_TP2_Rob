#pragma once


struct Block
{
    int x;
    int y;
	int z;
	int points;
    char value;	

	//pour savoir s'il a été exploré
    bool visited = false; 
	
	Block* upBlock = nullptr;
	Block* downBlock = nullptr;
	Block* leftBlock = nullptr;
	Block* frontBlock = nullptr;
	Block* rightBlock = nullptr;
	Block* behindBlock = nullptr;
	

	//Aide-mémoire : ces pointeurs représentent la priorité pour inspecter le labyrinthe
	//1. On regarde d'abord si on peut monter de niveau
	//2. Sinon si on peut descendre de niveau
	//3. Sinon si on peut tourner à gauche
	//4. Sinon si on peut aller tout droit
	//5. Sinon si on peut tourner à droite
	//6. Sinon si on peut aller vers le bas
	
	//7. Sinon c'est un cul-de-sac, on fait marche arrière pour tenter trouver un autre chemin

};