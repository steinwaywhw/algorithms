#ifndef _STACK_H
#define _STACK_H


typedef void (*fn_free_data) (void *data);

struct stack {
	int size;
	int top;
	void *data;
	fn_free_data fn;
};


struct stack* init_stack (int size, fn_free_data fn);
void destroy_stack (struct stack *s);
struct stack* resize (struct stack *s, int size);
void* pop (struct stack *s);
void* push (struct stack *s, void *data);

#endif
