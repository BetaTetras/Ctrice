/*
 * -=- Premier maquette non-fonctionelle -=-
 * Ce qui marche :
 * - Le display
 * - L'alternation des bloc (Carre et Barre)
 * - La base du refresh
 * - SetBloc correcte
*/


#include <stdio.h>   // Entrer / Sortie terminal 
#include <stdlib.h>  // Malloc,calloc ...
#include <string.h>  // Gestion de string
#include <conio.h>   // Gestion des entrée en continue 
#include <time.h>    // Gestion de l'aleatoire
#include <unistd.h>  // Gestion du Sleep
#include <windows.h> // Gestion terminal

/* -=- DEFINITION DE VARIABLE DE LA PARTIE -=- */
// Definit que les variable char* (Pointeur vers un caractere qui vas étre utilisée comme tableau de caractere) est une String 
typedef char* String;

// Def des type de bloc
typedef enum{
    CARRE,
    BARRE,
}BlocType;

// Définit un ensemble de variable utilise pour le jeu ...
struct DATA{
    int BoolAlive;
    int Score;

    int XplayerPosition;
    int YplayerPosition;

    int XposBloc2;
    int YposBloc2;

    int XposBloc3;
    int YposBloc3;

    int XposBloc4;
    int YposBloc4;

    BlocType ActualBloc;

    int** Tab;
};

/* -=- DEFINITION DE VARIABLE & REGLE -=- */


// Définit des mouvement et des touches
typedef enum{
    HAUT = 'z',
    BAS = 's',
    GAUCHE = 'q',
    DROITE = 'd',
} Direction;

/* -=- DEFINITION DE CONSTANTE -=- */
const int WIDTH = 10;
const int HEIGHT = 29;

const int XspawnPoint = 5;
const int YspawnPoint = 0;

/* -=- DEFINITION DES FONCTION -=- */

// Def fonction param
struct DATA SetUp();
struct DATA refresh(struct DATA Partie,Direction Dir);
struct DATA setBloc(struct DATA Partie);
// Def fonction Display
void Display(struct DATA Partie);
void DisplayDebug(struct DATA Partie);
// Def fonction COLOR
void printf_RED(String Text,...);
void printf_GREEN(String Text,...);
void printf_RED(String Text,...);
void printf_MAGENTA(String Text,...);
// Def fonction UI
void HideCursor();
void gotoxy(int WIDTH, int HEIGHT);
int TerminalUi(int Ystart,int n,...);

/*##################################################################################################################################################################################################*/
int main(){
    
    HideCursor();
    system("cls");

    Direction key; // Définition d'un char qui permettra de stockée le caractére entrée 
    char lastDirection = BAS; // Définition d'un char qui est égal a la derniére direction choisi pour que le serpent puisse avancée tout seul
    struct DATA Partie = SetUp();
    while(1){
        if(kbhit()){ // Si une touche est detecter
            key = getch(); // La touche est = la variable de key

            // Si la touche est valide alors lastDirection est = key pour stocket la dernier direction
            if(key == HAUT || key == BAS || key == GAUCHE || key == DROITE){
                lastDirection = key;
            }else if(key == 27){
                break;
            }
            
            Partie = refresh(Partie,key);
        }
        printf("\033[H");
        Display(Partie);
        // DisplayDebug(Partie);
    }
    return 0;
}


struct DATA SetUp(){
    int** Tab = (int**)calloc(HEIGHT,sizeof(int*));

    // Affectation de tout les colonne
    for(int i=0;i<HEIGHT;i++){
        Tab[i] = (int*)calloc(WIDTH,sizeof(int));
    }


    struct DATA Partie;
    Partie.BoolAlive = 1;
    Partie.Score = 0;
    Partie.Tab = Tab;

    Partie.ActualBloc = CARRE;

    Partie.XplayerPosition = 5;
    Partie.YplayerPosition = 12;

    return Partie;
}

struct DATA setBloc(struct DATA Partie){
    switch (Partie.ActualBloc)
    {
    case CARRE:
        //    [B3] [B4]
        //    [B2] [Jo]
        Partie.XposBloc2 = Partie.XplayerPosition-1;
        Partie.YposBloc2 = Partie.YplayerPosition;

        Partie.XposBloc3= Partie.XplayerPosition-1;
        Partie.YposBloc3 = Partie.YplayerPosition-1;

        Partie.XposBloc4 = Partie.XplayerPosition;
        Partie.YposBloc4 = Partie.YplayerPosition-1;
    break;

    case BARRE:
        // [B2]
        // [B3]
        // [Jo]
        // [B4]

        Partie.XposBloc2 = Partie.XplayerPosition;
        Partie.YposBloc2 = Partie.YplayerPosition - 2;

        Partie.XposBloc3 = Partie.XplayerPosition;
        Partie.YposBloc3 = Partie.YplayerPosition - 1;

        Partie.XposBloc4 = Partie.XplayerPosition;
        Partie.YposBloc4 = Partie.YplayerPosition + 1;
    break;
    }

    return Partie;
}

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

}

void DisplayDebug(struct DATA Partie){
    printf_MAGENTA("\n\nPos WIDTH : %d      Pos HEIGHT : %d\n",Partie.XplayerPosition,Partie.YplayerPosition);
}

struct DATA refresh(struct DATA Partie,Direction Dir){

    switch(Dir){
        case HAUT:
            // if(Partie.YplayerPosition != 0 && Partie.YposBloc2 != 0 && Partie.YposBloc3 != 0 && Partie.YposBloc4 != 0){
            //     Partie.YplayerPosition -- ;
            // }
            Partie.YplayerPosition -- ;
        break;

        case BAS:
            // if(Partie.YplayerPosition != HEIGHT-1 && Partie.YposBloc2 !=HEIGHT-1 && Partie.YposBloc3 !=HEIGHT-1 && Partie.YposBloc4 !=HEIGHT-1){
            //     Partie.YplayerPosition ++ ;
                
            //     Partie.Tab[Partie.YplayerPosition][Partie.XplayerPosition] = 3;
            //     Partie.Tab[Partie.YposBloc2][Partie.XposBloc2] = 3;
            //     Partie.Tab[Partie.YposBloc3][Partie.XposBloc3] = 3;
            //     Partie.Tab[Partie.YposBloc4][Partie.XposBloc4] = 3;

            //     srand(time(NULL));
            //     BlocType ListeBloc[2] = {CARRE,BARRE};
            //     Partie.ActualBloc = ListeBloc[rand() %2];

            //     Partie.YplayerPosition = 12;
            //     Partie.XplayerPosition = 5;
            // }
            Partie.YplayerPosition ++ ;
        break;

        case GAUCHE:
            // if(Partie.XplayerPosition != 0 && Partie.XposBloc2 != 0 && Partie.XposBloc3 != 0&& Partie.XposBloc4 != 0){
            //     Partie.XplayerPosition -- ; 
            // }
            Partie.XplayerPosition -- ;
        break;

        case DROITE:
            // if(Partie.XplayerPosition != WIDTH-1 && Partie.XposBloc2 != WIDTH-1 && Partie.XposBloc3 != WIDTH-1 && Partie.XposBloc4 != WIDTH-1){
            //     Partie.XplayerPosition ++ ; 
            // } 
            Partie.XplayerPosition ++ ;   
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

    Partie = setBloc(Partie);

    Partie.Tab[Partie.YplayerPosition][Partie.XplayerPosition] = 1;
    Partie.Tab[Partie.YposBloc2][Partie.XposBloc2] = 2;
    Partie.Tab[Partie.YposBloc3][Partie.XposBloc3] = 2;
    Partie.Tab[Partie.YposBloc4][Partie.XposBloc4] = 2;

    return Partie;
}


// ##############################################################################################################################################################################################

/* -=- PRINTF VERSION COLORER -=- */
void printf_GREEN(String Text,...){
    va_list Args;
    va_start(Args,Text);

    for(int i=0;i<strlen(Text);i++){
        if(Text[i] == '%'){
            if(Text[i+1] == 'd'){
                int _int = va_arg(Args,int);
                printf("\033[1;32m%d\033[0m",_int);
                i ++;
            }else if(Text[i+1] == 'f'){
                double _double = va_arg(Args,double);
                printf("\033[1;32m%f\033[0m",_double);
                i ++;
            }else if(Text[i+1] == 's'){
                String _String = va_arg(Args,String);
                printf("\033[1;32m%s\033[0m",_String);
                i ++;
            }else if(Text[i+1] == 'c'){
                int _char = va_arg(Args,int);
                printf("\033[1;32m%c\033[0m",_char);
                i++;
            }
        }else{
            printf("\033[1;32m%c\033[0m",Text[i]);
        }
    }

    va_end(Args);
}

void printf_RED(String Text,...){
    va_list Args;
    va_start(Args,Text);

    for(int i=0;i<strlen(Text);i++){
        if(Text[i] == '%'){
            if(Text[i+1] == 'd'){
                int _int = va_arg(Args,int);
                printf("\033[1;31m%d\033[0m",_int);
                i ++;
            }else if(Text[i+1] == 'f'){
                double _double = va_arg(Args,double);
                printf("\033[1;31m%f\033[0m",_double);
                i ++;
            }else if(Text[i+1] == 's'){
                String _String = va_arg(Args,String);
                printf("\033[1;31m%s\033[0m",_String);
                i ++;
            }else if(Text[i+1] == 'c'){
                int _char = va_arg(Args,int);
                printf("\033[1;31m%c\033[0m",_char);
                i++;
            }
        }else{
            printf("\033[1;31m%c\033[0m",Text[i]);
        }
    }

    va_end(Args);
}

void printf_MAGENTA(String Text,...){
    va_list Args;
    va_start(Args,Text);

    for(int i=0;i<strlen(Text);i++){
        if(Text[i] == '%'){
            if(Text[i+1] == 'd'){
                int _int = va_arg(Args,int);
                printf("\033[0;35m%d\033[0m",_int);
                i ++;
            }else if(Text[i+1] == 'f'){
                double _double = va_arg(Args,double);
                printf("\033[0;35m%f\033[0m",_double);
                i ++;
            }else if(Text[i+1] == 's'){
                String _String = va_arg(Args,String);
                printf("\033[0;35m%s\033[0m",_String);
                i ++;
            }else if(Text[i+1] == 'c'){
                int _char = va_arg(Args,int);
                printf("\033[0;35m%c\033[0m",_char);
                i++;
            }
        }else{
            printf("\033[0;35m%c\033[0m",Text[i]);
        }
    }

    va_end(Args);
}

void printf_BLUE(String Text,...){
va_list Args;
va_start(Args,Text);

for(int i=0;i<(int)strlen(Text);i++){
    if(Text[i] == '%'){
        if(Text[i+1] == 'd'){
            int _int = va_arg(Args,int);
            printf("\033[1;34m%d\033[0m",_int);
            i ++;
        }else if(Text[i+1] == 'f'){
            double _double = va_arg(Args,double);
            printf("\033[1;34m%f\033[0m",_double);
            i ++;
        }else if(Text[i+1] == 's'){
            String _String = va_arg(Args,String);
            printf("\033[1;34m%s\033[0m",_String);
            i ++;
        }else if(Text[i+1] == 'c'){
            int _char = va_arg(Args,int);
            printf("\033[1;34m%c\033[0m",_char);
            i++;
        }
    }else{
        printf("\033[1;34m%c\033[0m",Text[i]);
    }
}

va_end(Args);
}

/* -=- GESTION UI -=- */

void HideCursor() {
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;
    info.bVisible = FALSE;  // FALSE = cache le curseur
    SetConsoleCursorInfo(consoleHandle, &info);
}

void gotoxy(int WIDTH, int HEIGHT) {
    COORD coord = {WIDTH, HEIGHT};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
