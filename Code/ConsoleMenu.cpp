#include "stdafx.h"
#include "ConsoleMenu.h"
#include <iostream>
#include <chrono>
#include <thread>

ConsoleMenu::ConsoleMenu()
{

}

ConsoleMenu::~ConsoleMenu()
{
	delete cube;
	delete rob;
	cout << endl << "***** Cube and Rob destroyed. *****" << endl << endl;
}

/// <summary>
/// La méthode Run est le point central de notre programme.
/// </summary>															
void ConsoleMenu::run()											
{																		
	char input;
	char tabValidInputs[] = { '1', '2', 'q' };
	const int NB_ELEMENTS = 3;

	//Tant qu'il ne quitte pas, on demande à l'utilisateur ce qu'il veut faire.
	do
	{
		displayCredits();
		input = readValidInput(tabValidInputs, NB_ELEMENTS);

																		
	} while (manageSelection(input));						
}																		

/// <summary>
/// Lit un caractère entré par l'utilisateur.
/// </summary>
/// <param name="tabValidInputs">Tableau des caractères autorisés.</param>
/// <param name="nbElements">Nombre d'éléments du tableau des caractères autorisés.</param>
/// <returns> retourne le caractère entré par le joueur s'il est présent dans le tableau. </returns>
char ConsoleMenu::readValidInput(char tabValidInputs[], int nbElements) const
{
	displayMenu();
	string userEntry;
	cin >> userEntry;

	if (userEntry.size() == 1)
	{
		//Pour tous les caractères valides,
		for (int i = 0; i < nbElements; i++)
		{
			//Si notre entrée y est présente,
			if (tabValidInputs[i] == userEntry[0])
				//on retourne ce caractère.
				return userEntry[0];
		}
	}

	cout << "Votre entree doit etre une seule lettre correspondante au menu ci-dessus." << endl;
	system("pause");
	system("cls");

	return NULL;
}

/// <summary>
/// Permet d'afficher le menu de l'application à l'utilisateur du programme.
/// </summary>
void ConsoleMenu::displayMenu() const
{
	cout << "Que voulez-vous faire ? " << endl;
	cout << "Appuyez sur 1 pour solutionner l'algorithme du chemin de sortie" << endl;
	cout << "Appuyez sur 2 pour solutionner l'algorithme de tous les points" << endl;
	cout << "Appuyez sur q pour quitter le programme." << endl;
}

/// <summary>
/// Affiche les crédits à l'utilisateur du programme.
/// </summary>
void ConsoleMenu::displayCredits() const
{
	cout << " _________________________________________________________________ " << endl;
	cout << "|                       TRAVAIL PRATIQUE 2                        |" << endl;
	cout << "|                             R.O.B                               |" << endl;
	cout << "|                                                                 |" << endl;
	cout << "|                            AUTEURS  :                           |" << endl;
	cout << "|                                                                 |" << endl;
	cout << "|                       Jennifer  Marcotte                        |" << endl;
	cout << "|                               &                                 |" << endl;
	cout << "|                        William Crepault                         |" << endl;
	cout << "|                                                                 |" << endl;
	cout << "|                       mettant en vedette                        |" << endl;
	cout << "|                                                                 |" << endl;
	cout << "|                              Rob                                |" << endl;
	cout << "|                     Dans le role de R.O.B.                      |" << endl;
	cout << "|                               &                                 |" << endl;
	cout << "|                *****  JennWillRobExperts  *****                 |" << endl;
	cout << "|_________________________________________________________________|" << endl;
	cout << endl << endl;
}

/// <summary>
/// Gère les événements relatifs à l'entrée des touches clavier par l'utilisateur.
/// </summary>
/// <param name="entry">Caractère entré par l'utilisateur</param>
/// <returns> vrai pour une visualisation (touche 1 ou 2) 
/// faux si l'utilisateur entre q</returns>								
bool ConsoleMenu::manageSelection(char entry) 
{																		
	bool toContinue = true;

	switch (entry)
	{
																		
	case '1':															
	{		
		if (cube == nullptr)
		{
			InitCubeAndRob();
		}
		//Résolution du chemin de sortie
		try
		{
			Stack* solution;
			rob->solvePathToExit();
			cout << endl;
			displayROB(entry);
			cout << "La solution du chemin de sortie est :" << endl;
			solution = rob->getSolutionPathToExit();

			displaySolution(*solution);

			cube->resetAllVisitedBlocksToFalse();
		}
		catch (exception& e)
		{
			cout << e.what() << endl;
			system("pause");
			break;
		}
		system("pause");
		system("cls");
		break;
	}
	//Si l'utilisateur veut solutionner le labyrinthe,
	case '2':
	{
		if (cube == nullptr)
		{
			InitCubeAndRob();
		}
		//Résolution des points
		try
		{
			Queue* solution;
			rob->solveAllPoints(cube->getStartBlock());					// Ajout du bon paramètre (cube.getStartBlock());
			cout << endl;
			displayROB(entry);
			cout << "La solution des points est :" << endl;
			solution = rob->getSolutionAllPoints();

			displaySolution(*solution);

			cube->resetAllVisitedBlocksToFalse();
		}
		catch (exception& e)
		{
			//Si erreur, on affiche l'exception et on efface le labyrinthe.
			cout << e.what() << endl;
			system("pause");
			break;
		}
		system("pause");
		system("cls");
		break;
	}

	case 'q':															
										
		//On quitte le programme										
		toContinue = false;
		break;
	}
	return toContinue;
}

/// <summary>
/// Initialisation Dynamique des cube det rob, ils resteront 
/// vivant tout au long de la méthode manageSelection().
/// </summary>
void ConsoleMenu::InitCubeAndRob()
{
	/*******************************************************
	Il y a aussi un fichier de 10 étages de disponible dans le répertoire launcher
	NE PAS OUBLIER D'AJUSTER LA DIMENSION DANS CONSTANTS.H
	********************************************************/
	string path = "cube5.txt";
	
	cube = new Cube(path);												
	rob = new ROB(cube);												
}

void ConsoleMenu::displaySolution(DataStructure& solution) const
{
	solution.display();
}

void ConsoleMenu::displayROB(char entry) const							// Pour le plaisir :)
{
	cout << "               ______					" << endl;
	cout << "              |\\_____\\				" << endl;
	cout << "              \\|_0_0_|	Beep Beep!  " << endl;
	cout << "              __|  |___				" << endl;
	cout << "             /\\__----/_\\				" << endl;
	cout << "             ()--[  ]-()				" << endl;
	cout << "                |  |					" << endl;
	cout << "             ___|  |__					" << endl;
	cout << "            /\\___---__\\				" << endl;
	cout << "            \\/|________|				" << endl << endl;

	if (entry == '1')
	{
		this_thread::sleep_for(std::chrono::seconds(1));
		cout << "Je cherche le chemin dans le labyrinthe." << endl;
		this_thread::sleep_for(std::chrono::seconds(2));
		cout << "J'ai trouve la sortie." << endl << endl;
		this_thread::sleep_for(std::chrono::seconds(1));
	}
	else if (entry == '2')
	{
		this_thread::sleep_for(std::chrono::seconds(1));
		cout << "Je cherche les points dans le labyrinthe." << endl;
		this_thread::sleep_for(std::chrono::seconds(1));
		cout << "Plusieurs chemins possibles \"activer mode: R.O.B. recursif.\"" << endl;
		this_thread::sleep_for(std::chrono::seconds(2));
		cout << "\"Nous\" avons trouves tous les points." << endl << endl;
		this_thread::sleep_for(std::chrono::seconds(1));
	}
}

