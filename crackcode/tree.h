

typedef struct _tree {
    int data;
    struct _tree *left;
    struct _tree *right;
} tree_t;

tree_t* make_tree();
void destroy_tree(tree_t *t);

