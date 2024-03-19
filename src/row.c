#include <stdio.h>
#include <stdlib.h>

#include "../headers/card.h"
#include "../headers/row.h"

struct element {
    Card data;
    Element *next;
    Element *ant;
};

Row *createRow(){

    Row *newRow = (Row *)malloc(sizeof(Row));

    if (!newRow) return NULL;

    newRow->start = NULL;
    newRow->end = NULL;
    newRow->size = 0;

    return newRow;

}

int insertInRow(Row * row, struct card newCard){

    if (!row) return 0;

    Element *newElement = (Element *)malloc(sizeof(Element));

    newElement->ant = NULL;
    newElement->next = row->end;
    newElement->data = newCard;

    row->end->ant = newElement;

    row->end = newElement;

    return 1;

}

int removeFromRow(Row *row, Card *card){

    if (!row || !(row->start)) return 0;
    
    *card = row->start->data;
    
    Element *aux = row->start;

    row->start = aux->ant;
    row->start->next = NULL;

    free(aux);

    return 1;
}

int accessRow(Row *row, Card *card){
    
    if (!row || !(row->start)) return 0;
    
    *card = row->start->data;

    return 1;
}

int show(Row * row){

    if (!row || !(row->start)) return 0;

    Element *aux = row->end;

    while (aux) {
        printf("[%d | %d]; ", aux->data.numCard, aux->data.numCows);

        aux = aux->next;
    }

    return 1;

}

int sizeOfRow(Row *row){
    
    if (!row) return -1;

    return row->size;
}