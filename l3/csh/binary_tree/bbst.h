//balanced binary tree with red-black algo
enum bbst_node_color { RED, BLACK };

typedef struct bbst_node_t {
    void* key;
    void* value;
    struct bbst_node_t* left;
    struct bbst_node_t* right;
    struct bbst_node_t* parent;
    enum bbst_node_color color;
} *bbst_node;

typedef struct bbst_t {
    struct bbst_node_t* root;
} *bbst;

bbst bbst_create();

typedef int (*compare_func)(void* left, void* right);

void* bbst_lookup(bbst tree, void* key, compare_func compare);

void bbst_insert(bbst tree, void* key, void* value, compare_func compare);
