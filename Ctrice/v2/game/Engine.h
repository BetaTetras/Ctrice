#ifndef ENGINE_H
#define ENGINE_H

#include <stdio.h>   // Entrer / Sortie terminal 
#include <stdlib.h>
#include <time.h>

/* --- Constantes du jeu --- */
#define WIDTH 10   // largeur (colonnes)
#define HEIGHT 29   // hauteur (lignes)

/* --- Types de blocs --- */
typedef enum {
    CARRE,
    BARRE
} BlocType;

/* --- Directions --- */
typedef enum {
    HAUT = 'z',
    BAS = 's',
    GAUCHE = 'q',
    DROITE = 'd'
} Direction;

/* --- Structure principale --- */
struct DATA{
    int BoolAlive;
    int Score;
    int** Tab;

    BlocType ActualBloc;

    int XplayerPosition;
    int YplayerPosition;

    int XposBloc2, YposBloc2;
    int XposBloc3, YposBloc3;
    int XposBloc4, YposBloc4;
};

/* --- Fonctions principales --- */
struct DATA SetUp(void);
struct DATA setBloc(struct DATA Partie);
struct DATA refresh(struct DATA Partie, Direction Dir);
int canMove(struct DATA Partie,Direction Dir);

#endif // ENGINE_H
