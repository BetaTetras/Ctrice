#ifndef TOOLS_H
#define TOOLS_H

#include <stdio.h>   // Entrer / Sortie terminal 
#include <stdlib.h>  // Malloc,calloc ...
#include <string.h>  // Gestion de string
#include <windows.h> // Gestion terminal

#define WIDTH 10   // largeur (colonnes)
#define HEIGHT 29   // hauteur (lignes)

typedef char* String;

int** cleaningTab(int** Tab,int YtoClean);
int isFull(int* Ligne,int MaxX);

/* -=- PRINTF COLORÉS -=- */
void printf_GREEN(String Text,...);
void printf_RED(String Text,...);
void printf_MAGENTA(String Text,...);
void printf_BLUE(String Text,...);

/* -=- UI -=- */
void HideCursor();
void gotoxy(int x, int y);

#endif
