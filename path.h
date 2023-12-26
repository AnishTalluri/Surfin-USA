// Header file for CSE13s Section 1 asgn5 Fall 23
// path.h
// Made by Jess Srinivas
// DO NOT modify this file.

#include "graph.h"
#include "stack.h"

#include <inttypes.h>
#include <stdbool.h>

#ifndef PATH
#define PATH

struct path;
typedef struct path Path;

Path *path_create(uint32_t capacity);

void path_free(Path **pp);

uint32_t path_vertices(const Path *p);

uint32_t path_distance(const Path *p);

void path_add(Path *p, uint32_t val, const Graph *g);

uint32_t path_remove(Path *p, const Graph *g);

void path_copy(Path *dst, const Path *src);

void path_print(const Path *p, FILE *f, const Graph *g);

#endif
