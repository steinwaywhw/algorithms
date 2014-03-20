#include "linklist.h"
#include <malloc.h>
#include <stdlib.h>

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
        
    while (head->next != NULL)
        head = head->next;
        
    head->next = node;
    return head;
}

node_t* insert(node_t *head, node_t *node, int index) {
    if (head == NULL || node == NULL || index > length(node) - 1)
        return NULL;
        
    if (index == 0) {
        node->next = head;
        return node;
    }
    
    node_t *prev;
    node_t *old_head = head;
    
    while (index > 0) {
        prev = head;
        head = head->next;
        index--;
    }
    
    prev->next = node;
    node->next = head;
    
    return old_head;
}

node_t* remove(node_t *head, int index) {
    if (head == NULL || index > length(head) - 1)
        return NULL;
        
    node_t *prev = head;
    node_t *curr = head;
    while (index > 0) {
        prev = curr;
        curr = curr->next;
        index--;
    }
    
    prev->next = curr->next;
    return curr;
}

int length(node_t *head) {
    if (head == NULL)
        return 0;
        
    int l = 0;
    while (head != NULL) {
        head = head->next;
        l++;
    }
    
    return l;
}

node_t* replace(node_t *head, note_t *node, int index) {
    if (head == NULL || node == NULL || index > length(head) - 1)
        return NULL;
}
node_t* retrieve(node_t* head, int index);
