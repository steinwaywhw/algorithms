#include <stdlib.h>
#include <malloc.h>
#include "stack.h"

void destroy_stack(stack_t *s) {
    if (s != NULL) 
        free(s);
}

stack_t* _push(stack_t *s, int e) {
    if (s == NULL)
        abort();
        
    if (s->top == MAX_CAP)
        abort();
        
    s->data[s->top] = e;
    s->top++;
    
    return s;
}

int _pop(stack_t *s) {
    if (s == NULL)
        abort();
    
    if (s->top == 0)
        abort();
        
    s->top--;
    return s->data[s->top];
}

int _peak(stack_t *s) {
    if (s == NULL)
        abort();
        
    if (s->top == 0)
        return;
        
    return s->data[s->top-1];
}

int _is_empty(stack_t *s) {
    if (s == NULL)
        abort();
    
    return s->top == 0;
}

stack_t* make_stack() {
    stack_t *s = (stack_t *)malloc(sizeof(stack_t));
    if (s == NULL)
        abort();
    
    s->top = 0;
    s->push = _push;
    s->pop = _pop;
    s->peak = _peak;
    s->is_empty = _is_empty;
    
    return s;
}

