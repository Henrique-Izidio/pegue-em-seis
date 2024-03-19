#include <stdlib.h>
#include <time.h>

#include "../headers/card.h"
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

        Card nCard;

        nCard.numCard = numCard;
        nCard.player = 0;

        if (numCard % 10 == 0) {
            nCard.numCows = 3;
        } else if (numCard % 5 == 0) {

            nCard.numCows = 2;

            if (numCard % 11 == 0) nCard.numCows += 5;

        }else if (numCard % 11 == 0) {
            nCard.numCows = 5;
        }else{
            nCard.numCows = 1;
        }

        Element *nElement = (Element *)malloc(sizeof(Element));

        if (!nElement) return 0;

        nElement->data = nCard;
        nElement->next = deck->top;

        deck->top = nElement;
        deck->height += 1;

        return 1;
}

//* Já remove e acessa
int draw(Stack *deck, Card *card){
    
    if(!deck || !(deck->height)) return 0;

    Element *aux = deck->top;

    deck->top = aux->next;

    deck->height -= 1;

    *card = aux->data;

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