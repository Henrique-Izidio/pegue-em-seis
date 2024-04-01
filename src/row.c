#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>

#include "../headers/row.h"

struct rowElement {
    Card data;
    RowElement *next;
    RowElement *ant;
};

Row *createRow(){

    Row *newRow = (Row *)malloc(sizeof(Row));

    if (!newRow) return NULL;

    newRow->start = NULL;
    newRow->end = NULL;
    newRow->size = 0;

    return newRow;

}

int insertInRow(Row * row, Card newCard){

    if (!row) return 0;

    RowElement *newElement = (RowElement *)malloc(sizeof(RowElement));

    if (!newElement) return 0;

    newElement->ant = NULL;

    newElement->data = newCard;

    newElement->next = row->end;

    if (row->size > 0) {
        row->end->ant = newElement;
    }else{
        row->start = newElement;
    }

    row->end = newElement;
    row->size++;

    return 1;

}

int removeFromRow(Row *row, Card *card){

    if (!row || !(row->start)) return 0;
    
    RowElement *aux = row->start;

    *card = createCard(aux->data.numCard);

    row->start = aux->ant;
    if(row->start) row->start->next = NULL;
    else row->end = NULL;

    row->size--;

    free(aux);

    return 1;
}

int accessStartRow(Row *row, Card *card){
    
    if (!row || !(row->start)) return 0;
    
    *card = createCard(row->start->data.numCard);

    return 1;
}

int accessEndRow(Row *row, Card *card){
    
    if (!row || !(row->end)) return 0;
    
    *card = createCard(row->end->data.numCard);

    return 1;
}

int showRow(Row * row){

    if (!row || !(row->size)) return 0;

    RowElement *aux = row->start;

    while (aux) {
        printw("[");
        if (aux->data.numCard < 100) printw("0"); 
        if (aux->data.numCard < 10) printw("0"); 
        printw("%d] ", aux->data.numCard);

        aux = aux->ant;

        if(aux) printw("->");
    }

    return 1;

}

int sizeOfRow(Row *row){
    if (!row) return -1;
    return row->size;
}