#ifndef CARD_H
#define CARD_H

struct card {
    int numCard;
    int numCows;
    int player;
};

#endif /* CARD_H */

typedef struct card Card;

Card createCard(int);