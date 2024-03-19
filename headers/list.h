typedef struct element Element;

typedef struct list{
    struct element *start;
    int size;
} List;

List *create();
int insertInOrder(List *, struct card);
int accesIndex(List *, int, struct card *);
int removeIndex(List *, int);
int showList(List *);
int sizeList(List *);