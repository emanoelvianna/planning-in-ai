void AStar(State *const initial, State *const goal, int line, int column) {
    double runtime;
    clock_t start = clock();
    int expanded = 0;
    ListNode *closed = NULL;
    ListNode *open = NULL;
    ListNode *neighbors = NULL;
    Node *currentNode = NULL;
    if (!isGoal(initial, goal, line, column)) {
        int g = 0;
        int h = getManhattanHeuristic(initial, goal, line, column);
        pushNode(&open, createNode(initial, NULL, g, h));
        while (open != NULL) {
            currentNode = open->currentNode;
            if (isGoal(currentNode->state, goal, line, column)) {
                runtime = (double) (clock() - start) / CLOCKS_PER_SEC;
                printf("- MOVEMENT TO SOLUTION:\n");
                printSolutionPath(currentNode, line, column);
                printf("- DETAILS:\n");
                printf("Runtime = %g milliseconds\n", runtime);
                printf("Heuristic in the initial state = %d\n", h);
                printf("Nodes expanded = %d\n", expanded);
                printNodeStatus(currentNode, line, column);
                break;
            }
            // printNodeStatus(currentNode, line, column);
            popNode(&open);
            pushNode(&closed, currentNode);
            neighbors = getNeighbors(currentNode, goal, line, column);
            if (neighbors != NULL) {
                expanded++;
                removeDuplicatesNode(open, &neighbors, line, column);
                removeDuplicatesNode(closed, &neighbors, line, column);
                concatenateListOfNodes(&open, neighbors);
                bubble_sort(&open);
            }
        }
    }
}