#include "stack.h"

#include <stdlib.h>

typedef struct stack {
    uint32_t capacity;
    uint32_t top;
    uint32_t *items;
} Stack;

// Creates a stack, dynamically allocates space for it, and returns a pointer to it.
Stack *stack_create(uint32_t capacity) {
    // Attempt to allocate memory for a stack
    // Cast it to a stack pointer too!
    Stack *s = (Stack *) malloc(sizeof(Stack));
    s->capacity = capacity;
    s->top = 0;

    // We need enough memory for <capacity> numbers
    s->items = calloc(s->capacity, sizeof(uint32_t));

    // We created our stack, return it!
    return s;
}

// Frees all space used by a given stack, and sets the pointer to NULL.
void stack_free(Stack **sp) {
    // sp is a double pointer, so we have to check if it,
    // or the pointer it points to is null.
    if (sp != NULL && *sp != NULL) {
        // Of course, we have to remember to free the
        // memory for the array of items first,
        // as that was also dynamically allocated!
        // If we freed the Stack first then we would
        // not be able to access the array to free it.
        if ((*sp)->items) {
            free((*sp)->items);
            (*sp)->items = NULL;
        }

        // Free memory allocated for the stack
        free(*sp);
    }

    if (sp != NULL) {
        // Set the pointer to null! This ensures we dont ever do a double free!
        *sp = NULL;
    }
}

// Adds val to the top of the stack S, and increments the counter. Returns true if successful, false otherwise (ex: the stack is full).
bool stack_push(Stack *s, uint32_t val) {
    // If the stack is full, return false;
    if (stack_full(s)) {
        return false;
    }

    // Set val
    s->items[s->top] = val;

    // Move the top of the stack
    s->top++;

    return true;
}

/* 
 * Sets the integer pointed to by val to the last item on the stack, and removes the last item on the stack.
 * Returns true if successful, false otherwise. Remember that stack->top is not the index of the top value
 * of the stack.
*/
bool stack_pop(Stack *s, uint32_t *val) {
    // If the stack is empty, return false
    if (stack_empty(s)) {
        return false;
    }

    // Pop the value from the top of the stack and store it in the memory location pointed to by "val"
    *val = s->items[s->top - 1];

    // Decrement "top" so it adjusts the amount of elements in the stack
    s->top--;

    return true;
}

/*
 * Sets the integer pointed to by val to the last item on the stack, but does not modify the stack. Returns true
 * if successful, false otherwise. Remember that stack->top is not the index of the top value of the stack.
*/
bool stack_peek(const Stack *s, uint32_t *val) {
    // If the stack is empty, return false
    if (stack_empty(s)) {
        return false;
    }

    // Set the value from the top of the stack and store it in the memory location pointed to by "val"
    *val = s->items[s->top - 1];

    return true;
}

/*
 * Returns true if the stack is empty, false otherwise. A stack is empty when there are no elements in it.
*/
bool stack_empty(const Stack *s) {
    // Check if the stack has 0 elements in it
    if (s->top == 0) {
        return true;
    }

    return false;
}

/*
 * Returns true if the stack is full, false otherwise. A stack is full when the number of elements is equal to
 * the capacity.
*/
bool stack_full(const Stack *s) {
    // Check if the stack has hit its capacity amount of elements
    if (s->top == s->capacity) {
        return true;
    }

    return false;
}

/*
 * Returns the number of elements in the stack. An empty stack contains zero elements.
*/
uint32_t stack_size(const Stack *s) {
    return s->top;
}

/*
 * Overwrites dst with all the items from src. You should also make sure to update dst->top so that your code
 * knows how many items are now in the stack. Finally, although it’s unlikely to come up in this assignment as
 * all your Stacks will be the same length, we should consider that dst may not have a capacity large enough
 * to store every item from src. You can use the assert function to make sure that this is not the case (if it
 * does happen, it is likely an error in your code).
*/
void stack_copy(Stack *dst, const Stack *src) {
    // Check if the destination stack has enough capacity to hold all items from the source stack
    //assert(dst->capacity == src->top);

    // Copy each item from the source stack to the destination stack
    for (uint32_t i = 0; i < src->top; i++) {
        dst->items[i] = src->items[i];
    }

    // Update the top of the destination stack
    dst->top = src->top;
}

void stack_print(const Stack *s, FILE *f, char *cities[]) {
    for (uint32_t i = 0; i < s->top; i += 1) {
        fprintf(f, "%s\n", cities[s->items[i]]);
    }
}
