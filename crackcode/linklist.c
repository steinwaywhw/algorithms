#include "linklist.h"
#include <malloc.h>

node_t* make_node(int data) {
    node_t* node = (node_t*)malloc(sizeof(node_t));
    if (node == NULL)
        return NULL;
        
    node->data = data;
    node->next = NULL;
    
    return node;
}

void del_node(node_t *node) {
    if (node != NULL)
        free(node);
}

node_t* append(node_t *head, node_t *node) {
    if (head == NULL)
        return node;
        
    while (head.next != NULL)
        head = head.next;
}