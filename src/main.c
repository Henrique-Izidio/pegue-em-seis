#include <ncurses.h>

#include "../headers/game.h"

int main() {

    initscr();
    keypad(stdscr, TRUE);
    start_color();
    noecho();

    init_pair(1, COLOR_YELLOW, COLOR_BLACK);
    init_pair(2, COLOR_WHITE, COLOR_BLACK);

    int opt = menu();

    if (opt == 1) play(getPlayersNum());

    printw("\n\nrodou tudo\n");

    getch();

    endwin();

    return 1;

}