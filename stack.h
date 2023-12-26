// Header file for CSE13s Section 1 asgn5 Fall 23
// stack.h
// Made by Jess Srinivas
// DO NOT modify this file.

#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>

#ifndef STACK
#define STACK

struct stack;
typedef struct stack Stack;

Stack *stack_create(uint32_t capacity);

void stack_free(Stack **sp);

bool stack_push(Stack *s, uint32_t val);

bool stack_pop(Stack *s, uint32_t *val);

bool stack_peek(const Stack *s, uint32_t *val);

bool stack_empty(const Stack *s);

bool stack_full(const Stack *s);

uint32_t stack_size(const Stack *s);

void stack_copy(Stack *dst, const Stack *src);

void stack_print(const Stack *s, FILE *f, char *cities[]);

#endif
