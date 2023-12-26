#include "path.h"

#include "graph.h"
#include "stack.h"

#include <assert.h>
#include <stdlib.h>

typedef struct path {
    uint32_t total_weight;
    Stack *vertices;
} Path;

/* 
 * Creates a path data structure, containing a Stack and a weight of zero.
*/
Path *path_create(uint32_t capacity) {
    // Allocate memory for Path
    Path *p = (Path *) malloc(sizeof(Path));
    p->total_weight = 0;

    // Vertices stack created
    p->vertices = stack_create(capacity);

    return p;
}

/*
 * Frees a path, and all its associated memory
*/
void path_free(Path **pp) {
    if (pp != NULL && *pp != NULL) {
        Stack *temp_stack = (*pp)->vertices;
        stack_free(&temp_stack);
        free(*pp);
    }
    if (pp != NULL) {
        *pp = NULL;
    }
}

/*
 * Finds the number of vertices in a path.
*/
uint32_t path_vertices(const Path *p) {
    return stack_size(p->vertices);
}

/*
 * Finds the distance covered by a path.
*/
uint32_t path_distance(const Path *p) {
    return p->total_weight;
}

/*
 * Adds vertex val from graph g to the path. This function must also update the distance and length of the
 * path. When adding a vertex to an empty path, the distance should remain zero. Otherwise, you must look
 * up the distance from the most recent vertex to the new one and add that to the total weight. The distance
 * can be non-zero only when there are at least two cities in the path.
*/
void path_add(Path *p, uint32_t val, const Graph *g) {
    if (!stack_empty(p->vertices)) {
        uint32_t prev_val = 9999999;
        stack_peek(p->vertices, &prev_val);
        uint32_t w = graph_get_weight(g, prev_val, val);
        p->total_weight += w;
    }

    stack_push(p->vertices, val);
}

/*
 * Removes the most recently added vertex from the path. This function must also update the distance and
 * length of the path based on the adjacency matrix in the graph pointed to by g. When removing the last
 * vertex from a path, the distance should become zero. The distance can be non-zero only when there are at
 * least two cities in the path.
 *
 * Since the return value of this function was not specified in the original version of this assignment, we will
 * not require you to return anything specific. However, you’ll probably find that returning the index of the
 * removed vertex is the most useful for your DFS implementation.
*/
uint32_t path_remove(Path *p, const Graph *g) {
    uint32_t removed_vertex = 9999999;
    stack_pop(p->vertices, &removed_vertex);

    // If stack is empty or has less than 2 cities
    if (!stack_empty(p->vertices)) {
        uint32_t prev_vertex = 9999999;
        stack_peek(p->vertices, &prev_vertex);
        uint32_t w = graph_get_weight(g, prev_vertex, removed_vertex);
        p->total_weight -= w;
    } else {
        p->total_weight = 0;
    }

    return removed_vertex;
}
    

/*
 * Copies a path from src to dst.
*/
void path_copy(Path *dst, const Path *src) {
    // Create a path for dst with the capacity for src
    // dst = path_create(stack_size(src->vertices));

    // Copy the src stack into the dst stack
    stack_copy(dst->vertices, src->vertices);

    // Copy the src total weight into dst total weight
    dst->total_weight = src->total_weight;
}

/*
 * Prints the path stored, using the vertex names from g, to the file outfile. See the Section 8 for the exact
 * form of the print statement. This function should only print the names of the vertices. The rest of the
 * output is produced by tsp.c
*/
void path_print(const Path *p, FILE *f, const Graph *g) {
    assert(f != NULL);
    stack_print(p->vertices, f, graph_get_names(g));
    /*
    for (uint32_t i = 0; i < stack_size(p->vertices); i++) {
        fprintf(f, "%s\n", g->names[stack_pop()]);
    }
    */
    /*
    while (stack_size(p->vertices) > 0) {
        uint32_t val = 9999999;
        if (stack_pop(p->vertices, &val) == true) {
            fprintf(f, "%s\n", g->names[val]);
        }
    }
    */
}
