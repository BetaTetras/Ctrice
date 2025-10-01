#include "../game/Display.h"
#include "../game/Engine.h"
#include "../lib/Tools.h"

int main(){
    // Fonction pour cachée le curseur    
    HideCursor();

    // Clean le terminal
    system("cls");

    // Définition d'une direction (char)
    Direction key; // Définition d'un char qui permettra de stockée le caractére entrée 

    // SetUp de la structure du jeu
    struct DATA Partie = SetUp();
    while(1){

        if(kbhit()){ // Si une touche est detecter
            key = getch(); // La touche est = la variable de key

            if(key == 27){ // Si le joueur appuis sur ECHAP = quittée
                break;
            }
            
            // refresh
            Partie = refresh(Partie,key);
        }
        // On remes notre curseur en haut a droit du terminal pour récriture
        printf("\033[H");
        // On affiche la partie
        Display(Partie);
    }
    return 0;
}

