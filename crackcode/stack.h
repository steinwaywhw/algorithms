#define MAX_CAP 100

typedef struct _stack {
    int data[MAX_CAP];
    int top;            //next empty slot
    
    struct _stack* (*push)(struct _stack *s, int e);
    int (*pop)(struct _stack *s);
    int (*peak)(struct _stack *s);
    int (*is_empty)(struct _stack *s);
} stack_t;

stack_t* make_stack();
void destroy_stack(stack_t *s);

