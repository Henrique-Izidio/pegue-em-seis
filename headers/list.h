#include "card.h"

typedef struct listElement ListElement;

typedef struct list{
    struct listElement *start;
    int size;
} List;

List *createList();
int insertInOrder(List *, struct card);
int accesIndex(List *, int, struct card *);
int removeIndex(List *, int);
int showList(List *, int);
int sizeList(List *);
int countPoints(List *);