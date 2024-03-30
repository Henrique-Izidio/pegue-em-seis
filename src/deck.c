#include <ncurses.h>
#include <stdlib.h>
#include <time.h>

#include "../headers/deck.h"

struct element {
    Card data;
    Element *next;
};

Stack *createDeck(){
    
    Stack *deck = (Stack *)malloc(sizeof(Stack));

    if (deck == NULL) return NULL;

    deck->top = NULL;
    deck->height = 0;

    return deck;
}

int insertInDeck(Stack * deck, int numCard){

        if (!deck) return 0;

        Element *nElement = (Element *)malloc(sizeof(Element));

        if (!nElement) return 0;

        Card nCard = createCard(numCard);

        nElement->data = nCard;
        nElement->next = deck->top;

        deck->top = nElement;
        deck->height++;

        return 1;
}

//* Já remove e acessa
int draw(Stack *deck, Card *card){
    
    if(!deck || !(deck->height)) return 0;

    Element *aux = deck->top;

    if (!aux) return 0;
    
    deck->top = aux->next;

    *card = aux->data;

    free(aux);

    deck->height--;

    return 1;
}

int shuffleDeck(Stack *deck){

    if (!deck || !(deck->height)) return 0;

    srand(time(NULL));

    Element *aux = deck->top;

    for (int i = deck->height - 1; i > 0; i--) {
        
        int index = rand() % (i + 1);

        aux = deck->top;

        for (int j = 0; j < index; j++) {
            aux = aux->next;
        }

        Card temp = aux->data;

        aux->data = deck->top->data;

        deck->top->data = temp;

    }

    return 1;
}

int deckHeight(Stack *deck){
    return deck->height;
}

void printDeck(Stack *deck){

    if (!deck) return;

    Element *aux = deck->top;

    while (aux) {
        printw("%d -> ", aux->data.numCard);
        if (aux->data.numCard % 20 == 0) {
            printw("\n");
        }
        aux = aux->next;
    }

    printw(" || ");

    return;
}