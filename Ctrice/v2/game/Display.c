#include "Display.h"

/*
 *  -=- FONCTION DISPLAY -=-
 * Baleye l'espace de jeu et :
 * - Si Tab[Yi][Xi] == 0 -> case VIDE
 * - Si Tab[Yi][Xi] == 1 -> case Joueur
 * - Si Tab[Yi][Xi] == 2 -> case Bloc Joueur
 * - Si Tab[Yi][Xi] == 4 -> case Bloc placée
*/
void Display(struct DATA Partie){
    for(int i=4;i<HEIGHT;i++){
        for(int j=0;j<WIDTH;j++){
            if(Partie.Tab[i][j] == 0){
                printf("[ ]");
            }else if(Partie.Tab[i][j] == 1){
                printf_RED("[@]");
            }else if(Partie.Tab[i][j] == 2){
                printf_GREEN("[#]");
            }else if(Partie.Tab[i][j] == 3){
                printf_BLUE("[$]");
            }
        }
        printf("\n");
    }
    printf("\n\n");
    // Affichage du score
    printf_MAGENTA("Score : %d",Partie.Score);
}

void DisplayDebug(struct DATA Partie){
    printf_MAGENTA("\n\nPos WIDTH : %d      Pos HEIGHT : %d\n",Partie.XplayerPosition,Partie.YplayerPosition);
}