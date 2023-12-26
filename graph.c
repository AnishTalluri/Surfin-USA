#include "graph.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct graph {
    uint32_t vertices;
    bool directed;
    bool *visited;
    char **names;
    uint32_t **weights;
} Graph;

/* Creates a new graph struct, and returns a pointer to it. Initializes all items in the visited array to false. */
// Code provided by document (Jess and Ben)
Graph *graph_create(uint32_t vertices, bool directed) {
    Graph *g = calloc(1, sizeof(Graph));
    g->vertices = vertices;
    g->directed = directed;

    // use calloc to initialize everything with zeroes
    g->visited = calloc(vertices, sizeof(bool));
    g->names = calloc(vertices, sizeof(char *));

    // allocate g->weights with a pointer for each row
    g->weights = calloc(vertices, sizeof(g->weights[0]));

    // allocate each row in the adjacency matrix
    for (uint32_t i = 0; i < vertices; ++i) {
        g->weights[i] = calloc(vertices, sizeof(g->weights[0][0]));
    }
    return g;
}

/*
 * Frees all memory used by the graph. Take a close look at when memory is allocated in this function to be
 * sure you free everything! Double check with valgrind.
 * 
 * This function takes in a double pointer (Graph **; a pointer to a pointer) so that it can set the Graph
 * pointer (that gp points to) to NULL. If it didn’t do this, it would be possible to try to access the Graph
 * using a pointer that had already been freed. Using a value after freeing it has the potential to create serious
 * vulnerabilities. To avoid this, we set *gp to NULL to ensure that any attempt to use the Graph after freeing
 * it will immediately crash your program.
*/
void graph_free(Graph **gp) {
    Graph *g = *gp;
    // Since gp is a **, check if gp and the pointer is NULL
    if (gp != NULL && *gp != NULL) {
        for (uint32_t i = 0; i < g->vertices; ++i) {
            free(g->weights[i]);
        }

        free(g->weights);
        free(g->names);
        free(g->visited);

        free(g);
    }

    if (gp != NULL) {
        *gp = NULL;
    }
}

/*
 * Finds the number of vertices in a graph.
*/
uint32_t graph_vertices(const Graph *g) {
    return g->vertices;
}

/*
 * Adds an edge between start and end with weight weight to the adjacency matrix of the graph.
*/
void graph_add_edge(Graph *g, uint32_t start, uint32_t end, uint32_t weight) {
    // Make sure the vertices are within range
    if (start < g->vertices && end < g->vertices) {
        g->weights[start][end] = weight;

        // If the graph is undirected, make sure the vice-versa points has the same weight
        if (!g->directed) {
            g->weights[end][start] = weight;
        }
    }
}

/*
 * Looks up the weight of the edge between start and end and returns it.
*/
uint32_t graph_get_weight(const Graph *g, uint32_t start, uint32_t end) {
    return g->weights[start][end];
}

/*
 * Adds the vertex v to the list of visited vertices.
*/
void graph_visit_vertex(Graph *g, uint32_t v) { // Check if v is in the in bounds
    if (v < g->vertices) {
        g->visited[v] = true;
    }
}

/*
 * Removes the vertex v from the list of visited vertices.
*/
void graph_unvisit_vertex(Graph *g, uint32_t v) {
    // Check if v is in the in bounds
    if (v < g->vertices) {
        g->visited[v] = false;
    }
}

/*
 * Returns true if vertex v is visited in graph g, false otherwise.
*/
bool graph_visited(const Graph *g, uint32_t v) {
    // Returns true/false based on if visited[v] is true or false
    return g->visited[v];
}

/*
 * Gets the names of the every city in an array. Returns a double pointer – an array of strings – but not a
 * copy.
*/
char **graph_get_names(const Graph *g) {
    return g->names;
}

/* 
 * Gives the city at vertex v the name passed in. This function makes a copy of the name and stores it in
 * the graph object. The parameter is const to indicate that graph_add_vertex() cannot modify the string
 * passed into it.
 * 
 * The strdup() function makes a copy of the string, which is necessary (and means it must be freed later).
 * Otherwise, you wouldn’t be sure that the pointer passed into graph_add_vertex() would still be valid
 * as long as the Graph existed (for instance, the caller might pass in a buffer which they will later use for
 * something else). We also make sure that if we overwrite an existing name, the old one is freed.
 * 
 * Code provided by document (Jess and Ben)
*/
void graph_add_vertex(Graph *g, const char *name, uint32_t v) {
    if (g->names[v])
        free(g->names[v]);
    g->names[v] = strdup(name);
}

/*
 * Gets the name of the city with vertex v from the array of city names. This does not allocate a new string,
 * it simply returns the one stored in the Graph. g is const since this function doesn’t need to modify the
 * Graph, and its return type is const to prevent the caller from manipulating the string that it returns.
*/
const char *graph_get_vertex_name(const Graph *g, uint32_t v) {
    return g->names[v];
}

/*
 * Optionally, prints a human-readable representation of a graph. Even though this function is not required,
 * we strongly recommend that you implement it as it will aid in making sure that you are reading in the graph
 * correctly.
*/
void graph_print(const Graph *g) {
    for (uint32_t i = 0; i < g->vertices; i++) {
        for (uint32_t j = 0; j < g->vertices; j++) {
            printf("Start: %s, End: %s, Weight: %u", g->names[i], g->names[j], g->weights[i][j]);
        }
    }
}
