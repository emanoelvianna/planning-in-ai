void AStar(State *const initial, State *const goal, int line, int column) {
    int expansion = 1;
    ListNode *closed = NULL;
    ListNode *open = NULL;
    ListNode *children = NULL;
    Node *node = NULL;

    if (isGoal(initial, goal, line, column) == 0) {
        int g = 0;
        int h = getManhattanHeuristic(initial, goal, line, column);
        int f = g + h;
        pushNode(&open, createNode(initial, NULL, g, h));
//        printOfStateOfNode(open->currentNode, line, column);
        while (open != NULL) {
            node = open->currentNode;
            popNode(&open); // remove first element
            if (isGoal(node->state, goal, line, column) == 1) {
                showBoard(node->state, line, column);
                break;
            }
            pushNode(&closed, node);
            children = getChildren(goal, node, line, column);
            //printf("%d\n", expansion++);
//            printListNode(&children, line, column);
//            printf("----------\n");
            concatenateListOfNodes(&open, children);
            sortByCost(&open);
            //pushNode(&open, children->currentNode);
            //printOfStateOfNode(open->currentNode, line, column);
        }
    }
}