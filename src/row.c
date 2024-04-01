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
    
    *card = createCard(row->start->data.numCard);
    
    RowElement *aux = row->start;

    row->start = aux->ant;
    row->start->next = NULL;

    row->size--;

    free(aux);

    return 1;
}

int accessStartRow(Row *row, Card *card){
    
    if (!row || !(row->start)) return 0;
    
    *card = row->start->data;

    return 1;
}

int accessEndRow(Row *row, Card *card){
    
    if (!row || !(row->end)) return 0;
    
    *card = row->end->data;

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

        if(!aux) printw("->");
    }

    return 1;

}

int sizeOfRow(Row *row){
    
    if (!row) return -1;

    return row->size;
}