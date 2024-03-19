#include "../headers/deck.h"
#include "../headers/card.h"
#include <stdio.h>

int main() {

    Stack *deck = createDeck();

    if(!deck){
        printf("ERRO: Não foi possivel inicilizar o jogo - CreateDeck");
        return 0;
    }

    for (int i = 1; i <= 104; i++) {
        if(!insertInDeck(deck, i)){
            printf("ERRO: Não foi possivel inicilizar o jogo - InsertInDeck [%d]", i);
            return 0;
        }
    }

    if (!shuffleDeck(deck)) {
        printf("ERRO: Não foi possivel inicilizar o jogo - ShuffleDeck");
    }


    Card card = draw(deck);

    if (card.player == -1) {
        printf("Ocorreu um erro ao comprar a carta");
        return 0;
    }

    printf("[%d]", card.numCard);
    printf("[%d]", card.numCows);
    printf("[%d]", card.player);

    return 0;
}