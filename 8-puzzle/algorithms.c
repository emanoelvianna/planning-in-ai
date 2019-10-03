void AStar(State *const initial, State *const goal, int line, int column) {
    ListNode *closed = NULL;
    ListNode *open = NULL;
    ListNode *children = NULL;
    Node *currentNode = NULL;
    if (isGoal(initial, goal, line, column) == 0) {
        int g = 0;
        int h = getManhattanHeuristic(initial, goal, line, column);
        pushNode(&open, createNode(initial, NULL, g, h));
        while (open != NULL) {
            currentNode = open->currentNode;
            if (isGoal(currentNode->state, goal, line, column) == 1) {
                printf("SOLUTION:\n");
                printSolutionPath(currentNode, line, column);
                printf("----------\n");
                printNodeStatus(currentNode, line, column);
                break;
            } else {
                // printNodeStatus(currentNode, line, column);
            }
            popNode(&open); // remove first element
            pushNode(&closed, currentNode);
            children = getChildren(goal, currentNode, line, column);
            if (children != NULL) {
                concatenateListOfNodes(&open, children);
                bubble_sort(&open);
            }
        }
    } else {
        // showBoard(initial, line, column);
    }
}