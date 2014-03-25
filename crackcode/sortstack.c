#include "stack.h"
#include <string.h>
#include <stdio.h>

void sort(stack_t *s) {
    if (s == NULL || s->is_empty(s))
        return;
    
    int buf;
    stack_t *r = make_stack();
    
    while (!s->is_empty(s)) {
        buf = s->pop(s);
        while (!r->is_empty(r) && r->peak(r) > buf)
            s->push(s, r->pop(r));
        r->push(r, buf);
    }
    
    memcpy(s, r, sizeof(stack_t));
    destroy_stack(r);
}



int main() {
    stack_t *s = make_stack();
    s->push(s, 1)->push(s, 4)->push(s, 2)->push(s, 8);
    sort(s);
    
    while (!s->is_empty(s))
        printf("%3d", s->pop(s));
        
    
}