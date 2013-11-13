#include "stack.h"

#include <malloc.h>
#include <string.h>
#include <assert.h>

void default_free_data (void *data) {
	assert (data != NULL);
	free (data);
}

struct stack* init_stack (int size, fn_free_data fn) {
	struct stack *s = (struct stack *) malloc (sizeof (struct stack));
	assert (s != NULL);

	s->data = malloc (sizeof (void *) * size);
	assert (s->data != NULL);

	s->top = 0;
	s->size = size;
	s->fn = fn;
	if (fn == NULL)
		s->fn = default_free_data;

	return s;
}

void destroy_stack (struct stack *s) {
	assert (s != NULL);

	while (s->top > 0) {
		s->top--;
		(*(s->fn)) (s->data + s->top);
	}

	free (s->data);
	free (s);
}

struct stack* resize (struct stack *s, int size) {
	assert (s != NULL && size > 0);

	int min = s->top > size ? size : s->top;
	struct stack *new_stack = init_stack (size, s->fn);

	int i = 0;
	while (i < min) {
		push (new_stack, s->data + i);
	}

	free (s->data);
	free (s);

	return new_stack;
}


void* pop (struct stack *s) {
	assert (s != NULL);

	if (s->top == 0)
		return NULL;

	s->top--;
	void *ret = s->data + s->top;

}


void* push (struct stack *s, void *data) {
	assert (s != NULL);

	if (s->top == s->size)
		return NULL;

	void **p = (void **)s->data + s->top;
	*p = data;

	s->top++;

	return data;
}
