void AStar(State *const initial, State *const goal, int line, int column) {
    double averageHeuristic;
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
            averageHeuristic = averageHeuristic + currentNode->heuristic;
            if (isGoal(currentNode->state, goal, line, column)) {
                runtime = (double) (clock() - start) / CLOCKS_PER_SEC;
                averageHeuristic = averageHeuristic / currentNode->depth;
                printDetailsOfSolution(expanded, currentNode->depth, runtime, averageHeuristic, h);
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

void iterativeDeepening(State *const initial, State *const goal, int line, int column) {
    double averageHeuristic;
    int expanded = 0;
    double runtime;
    clock_t start = clock();
    ListNode *visitedNodes = NULL;
    ListNode *toVisit = NULL;
    ListNode *neighbors = NULL;
    Node *currentNode = NULL;

    int g = 0;
    int h = getManhattanHeuristic(initial, goal, line, column);
    pushNode(&toVisit, createNode(initial, NULL, g, h));
    while (1) {
        currentNode = toVisit->currentNode;
        averageHeuristic = averageHeuristic + currentNode->heuristic;
        if (isGoal(currentNode->state, goal, line, column)) {
            runtime = (double) (clock() - start) / CLOCKS_PER_SEC;
            averageHeuristic = averageHeuristic / currentNode->depth;
            printDetailsOfSolution(expanded, currentNode->depth, runtime, averageHeuristic, h);
            break;
        }
        popNode(&toVisit);
        pushNode(&visitedNodes, currentNode);
        neighbors = getNeighbors(currentNode, goal, line, column);
        if (neighbors != NULL) {
            expanded++;
            concatenateListOfNodes(&toVisit, neighbors);
        }
    }
}

void iterativeDeepeningAStar(State *const initial, State *const goal, int line, int column) {
    double averageHeuristic;
    int expanded = 0;
    double runtime;
    clock_t start = clock();
    ListNode *visitedNodes = NULL;
    ListNode *toVisit = NULL;
    ListNode *neighbors = NULL;
    Node *currentNode = NULL;

    int g = 0;
    int h = getManhattanHeuristic(initial, goal, line, column);
    pushNode(&toVisit, createNode(initial, NULL, g, h));
    while (1) {
        currentNode = toVisit->currentNode;
        averageHeuristic = averageHeuristic + currentNode->heuristic;
        if (isGoal(currentNode->state, goal, line, column)) {
            runtime = (double) (clock() - start) / CLOCKS_PER_SEC;
            averageHeuristic = averageHeuristic / currentNode->depth;
            printDetailsOfSolution(expanded, currentNode->depth, runtime, averageHeuristic, h);
            break;
        }
        popNode(&toVisit);
        pushNode(&visitedNodes, currentNode);
        neighbors = getNeighbors(currentNode, goal, line, column);
        if (neighbors != NULL) {
            expanded++;
            concatenateListOfNodes(&toVisit, neighbors);
            bubble_sort(&toVisit);
        }
    }
}

void greedySearch(State *const initial, State *const goal, int line, int column) {
    double averageHeuristic;
    int expanded = 0;
    double runtime;
    clock_t start = clock();
    ListNode *explored = NULL;
    ListNode *frontier = NULL;
    ListNode *neighbors = NULL;
    Node *currentNode = NULL;

    int g = 0;
    int h = getManhattanHeuristic(initial, goal, line, column);
    pushNode(&frontier, createNode(initial, NULL, g, h));
    while (frontier != NULL) {
        currentNode = frontier->currentNode;
        averageHeuristic = averageHeuristic + currentNode->heuristic;
        if (isGoal(currentNode->state, goal, line, column)) {
            runtime = (double) (clock() - start) / CLOCKS_PER_SEC;
            averageHeuristic = averageHeuristic / currentNode->depth;
            printDetailsOfSolution(expanded, currentNode->depth, runtime, averageHeuristic, h);
            break;
        }
        expanded++;
        pushNode(&explored, currentNode);
        neighbors = getNeighbors(currentNode, goal, line, column);
        if (neighbors != NULL) {
            expanded++;
            removeDuplicatesNode(frontier, &neighbors, line, column);
            removeDuplicatesNode(explored, &neighbors, line, column);
            concatenateListOfNodes(&frontier, neighbors);
            bubble_sort(&frontier);
        }
    }
}

void bfsGraph(State *const initial, State *const goal, int line, int column) {
    // TODO:
}