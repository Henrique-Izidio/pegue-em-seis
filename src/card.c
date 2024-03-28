#include "../headers/card.h"

Card createCard(int cardNum){

    Card newCard;

    newCard.numCard = cardNum;
    newCard.player = 0;

    if (cardNum % 10 == 0) {
        newCard.numCows = 3;
    } else if (cardNum % 5 == 0) {

        newCard.numCows = 2;

        if (cardNum % 11 == 0) newCard.numCows += 5;

    }else if (cardNum % 11 == 0) {
        newCard.numCows = 5;
    }else{
        newCard.numCows = 1;
    }

    return newCard;
}