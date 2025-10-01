#include "Engine.h"
#include "../lib/Tools.h"


/*
 *              -=- SETUP de la STRUCTURE -=-
 * Fonction qui initialise la structure DATA pour le déroulement
 * de la partie:
 *  - Mises en place de l'espace de jeu
 *  - Mises en place des coordonée
 *  - Mises en place de valeur flottante (Score)
 *  - Mises en place du bloc de base
*/
struct DATA SetUp(){

    // Création d'un tabeau en deux dimension
    int** Tab = (int**)calloc(HEIGHT,sizeof(int*));

    // Affectation de tout les colonne
    for(int i=0;i<HEIGHT;i++){
        Tab[i] = (int*)calloc(WIDTH,sizeof(int));
    }

    // On fais appelle a la structure de format DATA
    struct DATA Partie;
    
    Partie.BoolAlive = 1;           // -> Si le joueur est encore en vis
    Partie.Score = 0;               // -> Score du joueur
    Partie.Tab = Tab;               // -> Tableau de jeu

    Partie.ActualBloc = CARRE;      // -> Premier bloc du jeu == carre

    Partie.XplayerPosition = 5;     // -> Position X du joueuer 
    Partie.YplayerPosition = 12;    // -> Position Y du joueuer

    /* -=- Def des position des bloc -=- */
    Partie.XposBloc2 = 5-1;     
    Partie.YposBloc2 = 12;

    Partie.XposBloc3= 5-1;
    Partie.YposBloc3 = 12-1;

    Partie.XposBloc4 = 5;
    Partie.YposBloc4 = 12-1;

    // Retour de la structure préparée
    return Partie;
}

/*
 *              -=- setBloc -=-
 * Fonction qui mes en place le bloc autour du joueur 
 * selon la position du joueur.
*/
struct DATA setBloc(struct DATA Partie){
    switch (Partie.ActualBloc)
    {
    case CARRE: 
        Partie.XposBloc2 = Partie.XplayerPosition-1;
        Partie.YposBloc2 = Partie.YplayerPosition;

        Partie.XposBloc3= Partie.XplayerPosition-1;     // [B3] [B4]
        Partie.YposBloc3 = Partie.YplayerPosition-1;    // [B2] [Jo]

        Partie.XposBloc4 = Partie.XplayerPosition;
        Partie.YposBloc4 = Partie.YplayerPosition-1;
    break;

    case BARRE:
        Partie.XposBloc2 = Partie.XplayerPosition;
        Partie.YposBloc2 = Partie.YplayerPosition - 2;  
                                                        // [B2]
        Partie.XposBloc3 = Partie.XplayerPosition;      // [B3]
        Partie.YposBloc3 = Partie.YplayerPosition - 1;  // [Jo]
                                                        // [B4]
        Partie.XposBloc4 = Partie.XplayerPosition;
        Partie.YposBloc4 = Partie.YplayerPosition + 1;
    break;
    }

    return Partie;
}

/*
 *              -=- refresh -=-
 * Fonction qui mes a jour la structure de la 
 * partie est handle les différent événement:
 * - Vérification des collisions
 * - Action en cas de pose de bloc 
 * - Rafréchissement du tableau de jeu
 * - Détection de ligne pleine
*/
struct DATA refresh(struct DATA Partie,Direction Dir){
    switch(Dir){
        case HAUT:
            if(canMove(Partie,HAUT) == 1){   
                Partie.YplayerPosition -- ;
            }
        break;

        case BAS:
            if(canMove(Partie,BAS) == 1){   
                Partie.YplayerPosition ++ ;
            }else{
                Partie.Tab[Partie.YplayerPosition][Partie.XplayerPosition] = 3;
                Partie.Tab[Partie.YposBloc2][Partie.XposBloc2] = 3;
                Partie.Tab[Partie.YposBloc3][Partie.XposBloc3] = 3;
                Partie.Tab[Partie.YposBloc4][Partie.XposBloc4] = 3;

                srand(time(NULL));
                BlocType ListeBloc[2] = {CARRE,BARRE};
                Partie.ActualBloc = ListeBloc[rand() %2];

                Partie.YplayerPosition = 4;
                Partie.XplayerPosition = 4;
            }
        break;

        case GAUCHE:
            if(canMove(Partie,GAUCHE) == 1){   
                Partie.XplayerPosition -- ;
            }           
        break;

        case DROITE:
            if(canMove(Partie,DROITE) == 1){   
                Partie.XplayerPosition ++ ;
            }  
        break;
    }

    // Réinitialisation de la zone de jeu
    for(int i=0;i<HEIGHT;i++){
        for(int j=0;j<WIDTH;j++){
            if(Partie.Tab[i][j] < 3){
                Partie.Tab[i][j] = 0;
            } 
        }
    }

    for(int i=0;i<HEIGHT;i++){
        if(isFull(Partie.Tab[i],WIDTH) == 1){
            Partie.Tab = cleaningTab(Partie.Tab,i);
            Partie.Score += 1000;
        }
    }

    Partie = setBloc(Partie);

    Partie.Tab[Partie.YplayerPosition][Partie.XplayerPosition] = 1;
    Partie.Tab[Partie.YposBloc2][Partie.XposBloc2] = 2;
    Partie.Tab[Partie.YposBloc3][Partie.XposBloc3] = 2;
    Partie.Tab[Partie.YposBloc4][Partie.XposBloc4] = 2;

    return Partie;
}

/*
 *              -=- canMove -=-
 * Fonction qui vérifie depuis la structure et la
 * position des bloc Joueuer ou du joueur si il
 * peut se mouvoir dans la position souhaitée
*/
int canMove(struct DATA Partie,Direction Dir)
{
     switch (Dir) 
     { 
        case HAUT: // Pas important
            if(Partie.YplayerPosition != 0 && Partie.YposBloc2 != 0 && Partie.YposBloc3 != 0 && Partie.YposBloc4 != 0){
                return 1;
            }else{
                return 0;
            } 
        break;
        
        case BAS:
            // Si la position du joueur ou de l'un des bloc joueur est au niveau des bords alors on ne peux pas se mouvoir
            if (Partie.YplayerPosition + 1 >= HEIGHT ||
                Partie.YposBloc2 + 1 >= HEIGHT ||
                Partie.YposBloc3 + 1 >= HEIGHT ||
                Partie.YposBloc4 + 1 >= HEIGHT){
                return 0;
            }

            // Si la position du joueur ou de l'un des bloc joueur est au niveau d'un bloc placée alors on ne peux pas se mouvoir
            if (Partie.Tab[Partie.YplayerPosition + 1][Partie.XplayerPosition] >= 3 ||
                Partie.Tab[Partie.YposBloc2 + 1][Partie.XposBloc2] >= 3 ||
                Partie.Tab[Partie.YposBloc3 + 1][Partie.XposBloc3] >= 3 ||
                Partie.Tab[Partie.YposBloc4 + 1][Partie.XposBloc4] >= 3){
                return 0;
            }
                
            // On peut se mouvoire
            return 1;
        break;
        
        case DROITE:
            if(Partie.XplayerPosition + 1 >= WIDTH ||
               Partie.XposBloc2 + 1 >= WIDTH ||
               Partie.XposBloc2 + 1 >= WIDTH ||
               Partie.XposBloc2 + 1 >= WIDTH ){
                return 0;
            } 

            if (Partie.Tab[Partie.YplayerPosition][Partie.XplayerPosition+1] >= 3 ||
                Partie.Tab[Partie.YposBloc2][Partie.XposBloc2+1] >= 3 ||
                Partie.Tab[Partie.YposBloc3][Partie.XposBloc3+1] >= 3 ||
                Partie.Tab[Partie.YposBloc4][Partie.XposBloc4+1] >= 3){
                return 0;
            }
            return 1;
        break;
        
        case GAUCHE:
            if(Partie.XplayerPosition - 1 < 0 ||
               Partie.XposBloc2 - 1 < 0 ||
               Partie.XposBloc2 - 1 < 0 ||
               Partie.XposBloc2 - 1 < 0 ){
                return 0;
            } 

            if (Partie.Tab[Partie.YplayerPosition][Partie.XplayerPosition -1] >= 3 ||
                Partie.Tab[Partie.YposBloc2][Partie.XposBloc2-1] >= 3 ||
                Partie.Tab[Partie.YposBloc3][Partie.XposBloc3-1] >= 3 ||
                Partie.Tab[Partie.YposBloc4][Partie.XposBloc4-1] >= 3){
                return 0;
            }
            return 1;
        break; 
    }
    return 0;
}