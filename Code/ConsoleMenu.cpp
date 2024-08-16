#include "stdafx.h"
#include "ConsoleMenu.h"

ConsoleMenu::ConsoleMenu()
{
	
}


ConsoleMenu::~ConsoleMenu()
{

}

/// <summary>
/// La méthode Run est le point central de notre programme.
/// </summary>
void ConsoleMenu::run() const
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
/// Permet d'affichier le menu de l'application à l'utilisateur du programme.
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
	cout << "-------------------------------------------------------------------" << endl;
    cout << "|                       TRAVAIL PRATIQUE 2                        |" << endl;
    cout << "|                             R.O.B                               |" << endl;
    cout << "|                                                                 |" << endl;
    cout << "|                            AUTEURS  :                           |" << endl;
    cout << "|                       Jennifer  Marcotte                        |" << endl;
    cout << "|                               &                                 |" << endl;
    cout << "|                        William Crépault                         |" << endl;
    cout << "------------------------------------------------------------------|" << endl;
    cout << endl;
	cout << endl;
}

/// <summary>
/// Gère les événements relatifs à l'entrée des touches clavier par l'utilisateur.
/// </summary>
/// <param name="entry">Caractère entré par l'utilisateur</param>
/// <returns> vrai pour une visualisation (touche 1 ou 2) 
/// faux si l'utilisateur entre q</returns>
bool ConsoleMenu::manageSelection(char entry) const
{
    bool toContinue = true;
    /*******************************************************
    Il y a aussi un fichier de 10 étages de disponible dans le répertoire launcher
    NE PAS OUBLIER D'AJUSTER LA DIMENSION DANS CONSTANTS.H
    ********************************************************/
    string path = "cube5.txt";

    Cube cube(path);
    ROB rob(&cube);

    switch (entry)
    {
		
    case '1':
    {        
        //Résolution du chemin de sortie
        try
        {    
            Stack* solution;
			rob.solvePathToExit();
			cout << endl;
			cout << "La solution du chemin de sortie est :" << endl;
            solution = rob.getSolutionPathToExit();
            //TODO : Codez la méthode display solution et utilisez-là pour afficher la solution
            //       Voir directives à la fin du fichier
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
        //Résolution des points
		try
		{
            Queue* solution;
            rob.solveAllPoints(NULL);
			cout << endl;
            cout << "La solution des points est :" << endl;
			solution = rob.getSolutionAllPoints();
            //TODO : Codez la méthode display solution et utilisez-là pour afficher la solution
            //       Voir directives à la fin du fichier
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

