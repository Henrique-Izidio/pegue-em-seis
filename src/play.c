#include <ncurses.h>
#include <stdlib.h>
#include <time.h>

#include "../headers/card.h"
#include "../headers/list.h"
#include "../headers/deck.h"
#include "../headers/row.h"
#include "../headers/player.h"
#include "../headers/game.h"

int play(int playersNum){

    int setupRound(Stack *, Row **, PlayerHand *, int);
    PlayerHand *createHands(int);
    Row **createBoard();
    int selectFRomHand(Row **, PlayerHand);
    int getRow(List *, Row *);
    int selectRow(Row **);

    Stack *deck = createDeck();
    PlayerHand *players = createHands(playersNum);
    Row **table = createBoard();

    if (!players) {
        printw("Não foi possivel iniciar o jogo");

        return 0;
    }

    for (int i = 0; i < playersNum; i++) {
        players[i].hand = createList();

        players[i].collection = createList();
    }

    if(!setupRound(deck, table, players, playersNum)){
        printw("Não foi possivel iniciar o jogo");

        return 0;
    }

    while (players[0].hand->size) {

        int handIndex = selectFRomHand(table, players[0]);

        Card *auxCard_01 = (Card *)malloc(sizeof(Card));
        Card *auxCard_02 = (Card *)malloc(sizeof(Card));
        List *auxList = createList();

        for (int i = 0; i < playersNum; i++) {
            if (i) { // se i > 0 -> vez do BOT
                srand(time(NULL));
                handIndex = rand() % players[i].hand->size;
            }
            accesIndex(players[i].hand, handIndex, auxCard_01);
            removeIndex(players[i].hand, handIndex);

            auxCard_01->player = i;
            insertInOrder(auxList, *auxCard_01);
        }

        for (int i = 1; i <= playersNum; i++) {
            accesIndex(auxList, 1, auxCard_01);
            removeIndex(auxList, 1);

            int temp = 0;
            int tableIndex = -1;

            for (int j = 0; j < 4; j++) {
                accessEndRow(table[j], auxCard_02);

                if (auxCard_02->numCard < auxCard_01->numCard && temp < auxCard_02->numCard) {
                    temp = auxCard_02->numCard;
                    tableIndex = j;
                }
            }

            if(tableIndex == -1) {
                tableIndex = selectRow(table);
                getRow(players[i-1].collection, table[handIndex]);
            }
            
            insertInRow(table[tableIndex], *auxCard_01);

            if (table[tableIndex]->size >= 6) {
                getRow(players[i-1].collection, table[handIndex]);
                // get row 
            }
        }
    }

    return 1;
}

int setupRound(Stack *deck, Row **table, PlayerHand *players, int playersNum){

    if (!deck || !table || !players) return 0;

    for (int i = 104; i >= 1; i--) {
        if(!insertInDeck(deck, i)) return 0;
    }

    if(!shuffleDeck(deck)) return 0;

    Card *newCard = (Card *)malloc(sizeof(Card));

    if (!newCard) return 0;

    for (int i = 0; i < 4; i++) {

        draw(deck, newCard);

        if (!table[i]) return 0;

        insertInRow(table[i], *newCard);
    }

    for (int i = 0; i < playersNum; i++) {

        if (!(players[i].hand) || !(players[i].collection)) return 0;

        for (int j = 0; j < 10; j++) {
            draw(deck, newCard);
            insertInOrder(players[i].hand, *newCard);
        }
        
    }

    free(newCard);
    
    return 1;
}

int selectFRomHand(Row **table, PlayerHand player){

    int printBoard(Row **, PlayerHand, int);

    int opt = 1;
    int ch = 1;

    while(ch != '\n'){

        printBoard(table, player, opt);

        ch = getch();

        if(ch == KEY_LEFT && opt > 1) opt -= 1;
        if(ch == KEY_RIGHT && opt < player.hand->size) opt += 1;

    }

    return opt;

}

int printBoard(Row **table, PlayerHand player, int opt){

    if (!table) return 0;

    clear();

    for (int i = 0; i < 4; i++) {
        
        Row *actual = table[i];
        
        printw("\n%d: ", i+1);

        showRow(actual);
    }

    printw("\n Sua coleção: \n");

    showList(player.collection, 0);

    printw("\nEscolha qual carta da sua mão jogar...\n");

    showList(player.hand, opt);

    return 1;

}

PlayerHand *createHands(int playersNum){

    PlayerHand *players = (PlayerHand *)malloc(playersNum * sizeof(PlayerHand));

    return players;
}

Row **createBoard(){
    Row **table = (Row **)malloc(4 * sizeof(Row *));

    if (!table) return 0;

    for (int i = 0; i < 4; i++) {
        table[i] = createRow();
    }; 

    return table;
}

int getRow(List *collection, Row *row){

    Card *auxCard = (Card *)malloc(sizeof(Card));

    if (!auxCard) {
        printw("Não foi possivel alocar");
        getch();
    }

    printw("Não foi possivel alocar");
    getch();
    
    for (int i = 0; i < 5; i++) {
        removeFromRow(row, auxCard);

        printw("teste");
        getch();

        insertInOrder(collection, *auxCard);
    }

    free(auxCard);

    return 1;
}

int selectRow(Row **board){

    int opt = 1;
    int ch = 1;

    while(ch != '\n'){

        clear();

        printw("Escolha uma linha para pegar para si:\n");

        for (int i = 0; i < 4; i++) {
            if(opt == i) attron(COLOR_PAIR(1));
            else attron(COLOR_PAIR(2));

            showRow(board[i]);
            printw("\n");

            attroff(COLOR_PAIR(1));
            attroff(COLOR_PAIR(2));
        }

        ch = getch();

        if(ch == KEY_UP && opt > 0) opt -= 1;
        if(ch == KEY_DOWN && opt < 3) opt += 1;

    }

    return opt;

}