typedef struct card Card;

struct card {
    int numCard;
    int numCows;
    int player;
};

Card createCard(int);