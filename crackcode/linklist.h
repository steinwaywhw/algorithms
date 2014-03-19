


typedef struct _node {
    int data;
    struct _node *next;
} node_t;

node_t* make_node(int data);
void del_node(node_t *node);

node_t* append(node_t *head, node_t *node);
node_t* insert(node_t *head, node_t *node, int index);
node_t* replace(node_t *head, note_t *node, int index);
node_t* retrieve(node_t* head, int index);
node_t* remove(node_t *head, int index);
int length(node_t *head);
