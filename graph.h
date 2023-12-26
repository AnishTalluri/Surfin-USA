// Header file for CSE13s Section 1 asgn5 Fall 23
// graph.h
// Made by Jess Srinivas
// DO NOT modify this file.

#include <inttypes.h>
#include <stdbool.h>

#ifndef GRAPH
#define GRAPH

struct graph;
typedef struct graph Graph;

Graph *graph_create(uint32_t vertices, bool directed);

void graph_free(Graph **gp);

uint32_t graph_vertices(const Graph *g);

void graph_add_edge(Graph *g, uint32_t start, uint32_t end, uint32_t weight);

uint32_t graph_get_weight(const Graph *g, uint32_t start, uint32_t end);

void graph_visit_vertex(Graph *g, uint32_t v);

void graph_unvisit_vertex(Graph *g, uint32_t v);

bool graph_visited(const Graph *g, uint32_t v);

char **graph_get_names(const Graph *g);

void graph_add_vertex(Graph *g, const char *name, uint32_t v);

const char *graph_get_vertex_name(const Graph *g, uint32_t v);

void graph_print(const Graph *g);

#endif
