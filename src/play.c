#include <ncurses.h>
#include <stdlib.h>

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

    Stack *deck = createDeck();
    PlayerHand *players = createHands(playersNum);
    Row **table = createBoard();

    if (!players) {
        printw("Não foi possivel iniciar o jogo");

        return 0;
    }

    for (int i = 0; i < playersNum; i++) {        
        players[i].hand = createList();

        players[i].collection = createList();;
    }

    if(!setupRound(deck, table, players, playersNum)){
        printw("Não foi possivel iniciar o jogo");

        return 0;
    }

    selectFRomHand(table, players[0]);

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