#include <stdio.h>
#include <stdlib.h>

typedef struct edge {
    struct node* toNode;
    int weight;
} edge;

typedef struct node {
    int index;
    int number_of_edges; // Used for edge array construction
    edge *edges;
} node;

typedef struct graph {
    int number_of_nodes;
    node *nodes;
} graph;

// Graph functions
void appendEdge(node* n, edge* e);
node* getNode(graph* g, int index);
void addEdge(graph* g, node* fromNode, node* toNode, int weight);
edge* getEdgesFrom(graph* g, int index);

void initializeGraph(graph* g, int graphSize);
node* createNode(int index);
// End graph functions

// Queue functions
typedef struct queueItem {
    node* node;
    int priority;
} queueItem;
typedef struct minQueue {
    //
} minQueue;
// End queue functions

void initializeGraph(graph* g, int graphSize) {
    g->number_of_nodes = graphSize;
    g->nodes = (node*)malloc(sizeof(node) * g->number_of_nodes);
    int i;
    for(i=0; i<(g->number_of_nodes); i++) {
        node *newNode = (node*)malloc(sizeof(node));
        newNode->index = i+1; // Graph is not 0-indexed
        g->nodes[i] = *newNode;
    }
}

node* getNode(graph* g, int index) {
    return &(g->nodes[index-1]);
}

void appendEdge(node* n, edge* e) {
    if(n->number_of_edges == 0) { // No edges yet
        n->edges = malloc(sizeof(edge));
        n->number_of_edges = 1;
    } else { // Increase the edges array with realloc()
        n->number_of_edges = n->number_of_edges++;
        n->edges = realloc(n->edges, sizeof(edge) * n->number_of_edges);
    }
    n->edges[n->number_of_edges - 1] = *e;
}

void addEdge(graph* g, node* fromNode, node* toNode, int weight) {
    node* n = getNode(g, fromNode->index);
    edge* e = malloc(sizeof(edge));
    e->weight = weight;
    node* edgeToNode = getNode(g, toNode->index);
    e->toNode = edgeToNode;
    appendEdge(n, e);
}

node* createNode(int index) {
    node* newNode = malloc(sizeof(node));
    newNode->index = index;
    newNode->number_of_edges = 0;
    return newNode;
}

int main(void) {
    graph* g = malloc(sizeof(graph));
    initializeGraph(g, 6); // GRAPH SIZE 6 BURNED IN

    printf("Making nodes\n");
    printf("\tEdge 1\n");
    node* n1 = createNode(2);
    node* n2 = createNode(3);
    addEdge(g, n1, n2, 10);
    
    printf("\tEdge 2\n");
    node* n3= createNode(1);
    node* n4 = createNode(4);
    addEdge(g, n3, n4, 7);
    
    printf("\tEdge 3\n");
    node* n5 = createNode(1);
    node* n6 = createNode(3);
    addEdge(g, n5, n6, 3);
    
    printf("\tEdge 4\n");
    node* n7 = createNode(3);
    node* n8 = createNode(4);
    addEdge(g, n7, n8, 3);
    
    printf("\tEdge 5\n");
    node* n9 = createNode(4);
    node* n10 = createNode(5);
    addEdge(g, n9, n10, 1);
    printf("Done\n");
}