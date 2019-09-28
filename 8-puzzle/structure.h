typedef struct Node Node;
typedef struct State State;
typedef struct Node Node;
typedef struct ListNode ListNode;
typedef struct NodeList NodeList;

typedef enum Move {
    UP, DOWN, LEFT, RIGHT, NOT_APPLICABLE
} Movement;
struct State {
    Movement action;
    int **board;
};

struct ListNode {
    Node *currNode;
    struct ListNode *prevNode;
    struct ListNode *nextNode;
};

struct NodeList {
    unsigned int nodeCount;
    ListNode *head;
    ListNode *tail;
};

struct Node {
    unsigned int depth;
    unsigned int heuristic;
    State *state;
    Node *parent;
    NodeList *children;
};
