typedef struct playerHand {
    int player;
    int points;
    struct list *hand;
    struct list *collection;
} PlayerHand;