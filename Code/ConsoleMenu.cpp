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

}

/// <summary>
/// La m�thode Run est le point central de notre programme.
/// </summary>
void ConsoleMenu::run() const
{
    
   
    char input;
    char tabValidInputs[] = { '1', '2', 'q' };
    const int NB_ELEMENTS = 3;

    /*string path = "cube5.txt";
    Cube cube(path);
    ROB rob(&cube);*/

    //Tant qu'il ne quitte pas, on demande � l'utilisateur ce qu'il veut faire.
    do
    { 
		displayCredits();
		input = readValidInput(tabValidInputs, NB_ELEMENTS);
		
		
    } while (manageSelection(input/*, path, cube, rob*/));
	
}

/// <summary>
/// Lit un caract�re entr� par l'utilisateur.
/// </summary>
/// <param name="tabValidInputs">Tableau des caract�res autoris�s.</param>
/// <param name="nbElements">Nombre d'�l�ments du tableau des caract�res autoris�s.</param>
/// <returns> retourne le caract�re entr� par le joueur s'il est pr�sent dans le tableau. </returns>
char ConsoleMenu::readValidInput(char tabValidInputs[], int nbElements) const
{
	
    displayMenu();
    string userEntry;
    cin >> userEntry;
	
    if (userEntry.size() == 1)
    {
        //Pour tous les caract�res valides,
        for (int i = 0; i < nbElements; i++)
        {
            //Si notre entr�e y est pr�sente,
            if (tabValidInputs[i] == userEntry[0])
                //on retourne ce caract�re.
                return userEntry[0];
        }
    }

	 cout << "Votre entree doit etre une seule lettre correspondante au menu ci-dessus." << endl;
     system("pause");
	 system("cls");
  
	 return NULL;
}

/// <summary>
/// Permet d'afficher le menu de l'application � l'utilisateur du programme.
/// </summary>
void ConsoleMenu::displayMenu() const
{
    cout << "Que voulez-vous faire ? " << endl;
    cout << "Appuyez sur 1 pour solutionner l'algorithme du chemin de sortie" << endl;
    cout << "Appuyez sur 2 pour solutionner l'algorithme de tous les points" << endl;
    cout << "Appuyez sur q pour quitter le programme." << endl;
}

/// <summary>
/// Affiche les cr�dits � l'utilisateur du programme.
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
/// G�re les �v�nements relatifs � l'entr�e des touches clavier par l'utilisateur.
/// </summary>
/// <param name="entry">Caract�re entr� par l'utilisateur</param>
/// <returns> vrai pour une visualisation (touche 1 ou 2) 
/// faux si l'utilisateur entre q</returns>
bool ConsoleMenu::manageSelection(char entry/*, string path, Cube cube, ROB rob*/) const
{
    bool toContinue = true;
    /*******************************************************
    Il y a aussi un fichier de 10 �tages de disponible dans le r�pertoire launcher
    NE PAS OUBLIER D'AJUSTER LA DIMENSION DANS CONSTANTS.H
    ********************************************************/
    string path = "cube5.txt";
    Cube cube(path);                    // Si on essais de r�soudre la r�initialisation du cube � chaque choix, commenter les 3 lignes 125, 126, 127
    ROB rob(&cube);

    switch (entry)
    {
		
    case '1':
    {        
        //R�solution du chemin de sortie
        try
        {    
            Stack* solution;
			rob.solvePathToExit();
			cout << endl;
            displayROB(entry);
			cout << "La solution du chemin de sortie est :" << endl;
            solution = rob.getSolutionPathToExit();  

            displaySolution(*solution);

			cube.resetAllVisitedBlocksToFalse();
            
        }
        catch (exception &e)
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
        //R�solution des points
		try
		{
            Queue* solution;
            rob.solveAllPoints(cube.getStartBlock());                           // Ajout du bon param�tre (cube.getStartBlock());
			cout << endl;
            displayROB(entry);
            cout << "La solution des points est :" << endl;
			solution = rob.getSolutionAllPoints();

            displaySolution(*solution);

			cube.resetAllVisitedBlocksToFalse();
		}
		catch (exception &e)
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

void ConsoleMenu::displaySolution(DataStructure& solution) const
{ 
    solution.display();
}
void ConsoleMenu::displayROB(char entry) const
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

