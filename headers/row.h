#include "card.h"

typedef struct element Element;

typedef struct row {
    Element *start;
    Element *end;
    int size;
} Row;

Row *createRow();
int insertInRow(Row *, struct card);
int removeFromRow(Row *, struct card *);
int accessRow(Row *, struct card *);
int showRow(Row *);
int sizeOfRow(Row *);