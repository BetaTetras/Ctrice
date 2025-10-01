#include "Tools.h"

int** cleaningTab(int** Tab,int YtoClean){
    int** NewTab = (int**)calloc(HEIGHT,sizeof(int*));

    for(int i=HEIGHT-1;i > YtoClean-1;i--){
        NewTab[i] = Tab[i];
    }

    for(int i=YtoClean;i > 0;i--){
        NewTab[i] = Tab[i-1];
    }

    NewTab[0] = (int*) calloc(WIDTH, sizeof(int));

    for(int i=0;i<WIDTH;i++){
        NewTab[0][i] = 0;
    }

    return NewTab;
}

int isFull(int* Ligne,int MaxX){
    for(int i=0;i<MaxX;i++){
        if(Ligne[i] < 3){
            return 0;
        }
    }
    return 1;
}
/* -=- PRINTF VERSION COLORER -=- */
void printf_GREEN(String Text,...){
    va_list Args;
    va_start(Args,Text);

    for(int i=0;i<(int)strlen(Text);i++){
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

    for(int i=0;i<(int)strlen(Text);i++){
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

    for(int i=0;i<(int)strlen(Text);i++){
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

for(int i=0;i<(int)(int)strlen(Text);i++){
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

void gotoxy(int x, int y) {
    COORD coord = {x, y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}