#include <malloc.h>
#include <stdlib.h>

#define MAX_CAP 100

typedef struct _stack {
    int data[MAX_CAP];
    int top;            //next empty slot
    
    void (*push)(struct _stack *s, int e);
    void (*pop)(struct _stack *s);
    int (*peak)(struct _stack *s);
    void (*is_empty)(struct _stack *s);
} stack_t;

stack_t* make_stack() {
    stack_t *s = (stack_t *)malloc(sizeof(stack_t));
    if (s == NULL)
        abort();
    
    s->top = 0;
    s->push = _push;
    s->pop = _pop;
    s->peak = _peak;
    s->is_empty = is_empty;
    
    return s;
}

void destroy_stack(stack_t *s) {
    if (s != NULL) 
        free(s);
}

void _push(stack_t *s, int e) {
    if (s == NULL)
        abort();
        
    if (s->top == MAX_CAP)
        abort();
        
    s->data[s->top] = e;
    s->top++;
}

void _pop(stack_t *s) {
    if (s == NULL)
        abort();
    
    if (s->top == 0)
        return;
        
    s->top--;
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