#include "card.h"

typedef struct element Element;

typedef struct stack{
    struct element *top;
    int height;
} Stack;

Stack *createDeck();
int insertInDeck(Stack *, int);
int draw(Stack *, struct card *); // Já remove e acessa
int shuffleDeck(Stack *);
int deckHeight(Stack *);
void printDeck(Stack *);
