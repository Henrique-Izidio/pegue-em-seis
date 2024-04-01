#include "card.h"

typedef struct rowElement RowElement;

typedef struct row {
    RowElement *start;
    RowElement *end;
    int size;
} Row;

Row *createRow();
int insertInRow(Row *, struct card);
int removeFromRow(Row *, struct card *);
int accessStartRow(Row *, struct card *);
int accessEndRow(Row *, struct card *);
int showRow(Row *);
int sizeOfRow(Row *);