#include <ncurses.h>
#include "../headers/game.h"

int menu() {

    void printMenu(int);

    int opt = 1;
    int ch = '1';

    while (ch != '\n') {

        printMenu(opt);

        ch = getch();

        if(ch == KEY_UP && opt < 1) opt += 1;
        if(ch == KEY_DOWN && opt > 0) opt -= 1;

    }

    return opt;
}

int getPlayersNum(){

    void printPlayersNum(int);

    int opt = 1;
    int ch = '1';

    while (ch != '\n') {

        printPlayersNum(opt);

        ch = getch();

        if(ch == KEY_LEFT && opt > 1) opt -= 1;
        if(ch == KEY_RIGHT && opt < 10) opt += 1;

    }

    return opt;
}

void printPlayersNum(int opt) {

    clear();

    printw("===== Selecione o Número de Jogadores =====\n\n");

    for (int i = 1; i <= 10; i++) {
        if(opt == i) attron(COLOR_PAIR(1));
        else attron(COLOR_PAIR(2));
        
        printw(" [%d]", i);

        attroff(COLOR_PAIR(1));
        attroff(COLOR_PAIR(2));
    }

    printw("\n\n===========================================\n\n");
    
    refresh();
}

void printMenu(int opt) {

    clear();

    printw("==== PEGUE EM SEIS ====\n\n");

    if(opt == 1) attron(COLOR_PAIR(1));
    else attron(COLOR_PAIR(2));

    printw(" 1 - Jogar\n");

    attroff(COLOR_PAIR(1));
    attroff(COLOR_PAIR(2));
    

    if(opt == 0) attron(COLOR_PAIR(1));
    else attron(COLOR_PAIR(2));

    printw(" 2 - Sair\n");

    attroff(COLOR_PAIR(1));
    attroff(COLOR_PAIR(2));

    printw("=======================\n\n");
    
    refresh();
}