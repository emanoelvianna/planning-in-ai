typedef struct Node Node;
typedef struct State State;
typedef struct Node Node;
typedef struct ListNode ListNode;

typedef enum Movement {
    UP, DOWN, LEFT, RIGHT, NOT_APPLICABLE
} Movement;

struct State {
    Movement action;
    int **board;
};

struct ListNode {
    Node *currentNode;
    struct Node *nextNode;
};

struct Node {
    unsigned int depth; // g
    unsigned int heuristic; // h
    State *state;
    Node *parent;
    ListNode *children;
};


