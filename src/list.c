#include <stdio.h>
#include <stdlib.h>

#include "../headers/card.h"
#include "../headers/list.h"

struct element {
    Card data;
    Element *next;
    Element *ant;
};

List *createList(){

    List *newList = (List *)malloc(sizeof(List));

    if (!newList) return NULL;

    newList->size = 0;
    newList->start = NULL;

    return newList;
}

int insertInOrder(List *ldse, Card newCard){

    if (!ldse) return 0;

    Element *newElement = (Element *)malloc(sizeof(Element));

    if (!newElement) return 0;

    newElement->data = newCard;
    newElement->next = NULL;
    newElement->ant = NULL;

    if (!(ldse->start)) {
        ldse->start = newElement;
        return 1;
    }

    Element *aux = ldse->start;

    while(aux->next){

        if (aux->data.numCard > newElement->data.numCard) {
            newElement->ant = aux->ant;
            if (!(aux->ant)) aux->ant->next = newElement;
            newElement->next = aux;
            ldse->size += 1;
            return 1;
        }

    }

    newElement->next = aux->next;
    aux->next = newElement;
    ldse->size += 1;

    return 1;
}

int accesIndex(List *ldse, int index, Card *card){

    if (!ldse || !(ldse->start)) return 0;

    Element *aux = ldse->start;
    int counter = 1;

    while(aux && counter < index){

        counter++;
        
        aux = aux->next;

    }

    if(!aux) return 0;

    *card = aux->data;

    return 1;
}

int removeIndex(List *ldse, int index){

    if (!ldse || !(ldse->start)) return 0;

    Element *aux = ldse->start;
    int counter = 1;

    while(aux && counter < index){

        counter++;
        
        aux = aux->next;

    }

    if(!aux) return 0;

    if (index == 1) ldse->start = aux->next;
    if(aux->ant) aux->ant->next = aux->next;
    if(aux->next)aux->next->ant = aux->ant;
    ldse->size -= 1;

    free(aux);

    return 1;

}

int showList(List *ldse){

    if (!ldse) return 0;

    Element *aux = ldse->start;

    while (aux) {
        printf("[");
        if(aux->data.numCard < 100) printf("0");
        if(aux->data.numCard < 10) printf("0");
        printf("%d]", aux->data.numCard);

        aux = aux->next;

        if(!aux) printf("->");
    }

    return 1;
}

int sizeList(List *ldse){
    if(!ldse) return -1;
    return ldse->size;
}