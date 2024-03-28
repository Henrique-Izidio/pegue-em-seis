#include <stdio.h>
#include <stdlib.h>

#include "../headers/card.h"
#include "../headers/game.h"
#include "../headers/deck.h"
#include "../headers/list.h"
#include "../headers/row.h"
#include "../headers/player.h"


int play(int playersNum){

    int setupGame(Stack *, Row **, PlayerHand *, int);
    void printTable(Row **, PlayerHand);

    Stack *deck;
    PlayerHand *players; 
    Row **table; 


    if(!setupGame(deck, table, players, playersNum)){
        printf("Não foi possivel iniciar o jogo");

        return 0;
    }

    printTable(table, players[0]);

    return 1;
}

int setupGame(Stack *deck, Row **table, PlayerHand *players, int playersNum){
    deck = createDeck();

    for (int i = 1; i <= 104; i++) {
        if(!insertInDeck(deck, i)) return 0;
    }

    if(!shuffleDeck(deck)) return 0;

    table = (Row **)malloc(4 * sizeof(Row *));

    if (!table) return 0;

    for (int i = 0; i < 4; i++) {
        table[i] = (Row *)malloc(sizeof(Row));
        if (!table[i]) return 0;
    }

    players = (PlayerHand *)malloc(playersNum * sizeof(PlayerHand));

    if(!players) return 0;

    for (int i = 0; i < playersNum; i++) {
        players[i].player = i+1;

        List *hand = (List *)malloc(sizeof(List));

        if (!hand) return 0;
        
        players[i].hand = hand;

        List *collection = (List *)malloc(sizeof(List));

        if (!collection) return 0;

        players[i].collection = collection;
    }

    Card *newCard;

    for (int i = 0; i < 4; i++) {
        draw(deck, newCard);
        insertInRow(table[i], *newCard);
    }
    
    return 1;
}

void printTable(Row **table, PlayerHand player){

    for (int i = 0; i < 4; i++) {
        
        Row *actual = table[i];

        showRow(actual);

        printf("\n");

    }

    printf("Sua coleção: ");

    showList(player.collection);


    printf("\nSua mão:\n");
    
    showList(player.hand);

    printf("\n");

    for (int i = 1; i <= (player.hand)->size; i++) {

        printf("( %d )", i);

        if(i != (player.hand)->size) printf("  ");

    }

    printf("\n\n");

    printf("Escolha qual carta da sua mão jogar...\n-> ");

}