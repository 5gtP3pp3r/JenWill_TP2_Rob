#include "stdafx.h"
#include "ConsoleMenu.h"

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

    //Tant qu'il ne quitte pas, on demande � l'utilisateur ce qu'il veut faire.
    do
    { 
		displayCredits();
		input = readValidInput(tabValidInputs, NB_ELEMENTS);
		
		
    } while (manageSelection(input));
	
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
/// Permet d'affichier le menu de l'application � l'utilisateur du programme.
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
	cout << "-------------------------------------------------------------------" << endl;
    cout << "|                       TRAVAIL PRATIQUE 2                        |" << endl;
    cout << "|                             R.O.B                               |" << endl;
    cout << "|                                                                 |" << endl;
    cout << "|                            AUTEURS  :                           |" << endl;
    cout << "|                       Jennifer  Marcotte                        |" << endl;
    cout << "|                               &                                 |" << endl;
    cout << "|                        William Cr�pault                         |" << endl;
    cout << "------------------------------------------------------------------|" << endl;
    cout << endl;
	cout << endl;
}

/// <summary>
/// G�re les �v�nements relatifs � l'entr�e des touches clavier par l'utilisateur.
/// </summary>
/// <param name="entry">Caract�re entr� par l'utilisateur</param>
/// <returns> vrai pour une visualisation (touche 1 ou 2) 
/// faux si l'utilisateur entre q</returns>
bool ConsoleMenu::manageSelection(char entry) const
{
    bool toContinue = true;
    /*******************************************************
    Il y a aussi un fichier de 10 �tages de disponible dans le r�pertoire launcher
    NE PAS OUBLIER D'AJUSTER LA DIMENSION DANS CONSTANTS.H
    ********************************************************/
    string path = "cube5.txt";

    Cube cube(path);
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
			cout << "La solution du chemin de sortie est :" << endl;
            solution = rob.getSolutionPathToExit();
            //TODO : Codez la m�thode display solution et utilisez-l� pour afficher la solution
            //       Voir directives � la fin du fichier
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
            rob.solveAllPoints(NULL);
			cout << endl;
            cout << "La solution des points est :" << endl;
			solution = rob.getSolutionAllPoints();
            //TODO : Codez la m�thode display solution et utilisez-l� pour afficher la solution
            //       Voir directives � la fin du fichier
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

