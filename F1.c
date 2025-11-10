
// node
typedef struct node {
    int val;
    struct node *next;
} node;

typedef struct {
    node *start;
    node *end;
    int size;
} queue;
