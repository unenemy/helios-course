#include "bbst.h"
#include <stdlib.h>
#include <assert.h>

typedef bbst_node node;
typedef enum bbst_node_color color;

static node grandparent(node n);
static node sibling(node n);
static node uncle(node n);
static node new_node(void* key, void* value, color node_color, node left, node right);
static color node_color(node n);
static void replace_node(bbst tree, node old_node, node new_node);
static void rotate_right(bbst tree, node n);
static void rotate_left(bbst tree, node n);
static node lookup_node(bbst tree, void* key, compare_func compare);
static void insert_case1(bbst tree, node n);
static void insert_case2(bbst tree, node n);
static void insert_case3(bbst tree, node n);
static void insert_case4(bbst tree, node n);
static void insert_case5(bbst tree, node n);
static node maximum_node(node root);
static void delete_case1(bbst tree, node n);
static void delete_case2(bbst tree, node n);
static void delete_case3(bbst tree, node n);
static void delete_case4(bbst tree, node n);
static void delete_case5(bbst tree, node n);
static void delete_case6(bbst tree, node n);

node grandparent(node n){
    assert(n != NULL);
    assert(n->parent != NULL);
    assert(n->parent->parent != NULL);
    return n->parent->parent;
}

node sibling(node n){
    assert(n != NULL);
    assert(n->parent != NULL);
    if(n->parent->left == n){
        return n->parent->right;
    }else {
        return n->parent->left;
    }
}

node uncle(node n){
    assert(n != NULL);
    assert(n->parent != NULL);
    assert(n->parent->parent != NULL);
    return sibling(n->parent);
}

color node_color(node n){
    return n == NULL ? BLACK : n->color;
}

node new_node(void* key, void* value, color node_color, node left, node right){
    node result = malloc(sizeof(struct bbst_node_t));
    result->key = key;
    result->value = value;
    result->color = node_color;
    result->left = left;
    result->right = right;
    if(left != NULL)left->parent = result;
    if(right != NULL)right->parent = result;
    result->parent = NULL;
    return result;
}

bbst bbst_create(){
    bbst tree = malloc(sizeof(struct bbst_t));
    tree->root = NULL;
    return tree;
}

node lookup_node(bbst tree, void* key, compare_func compare){
    node n = tree->root;
    while(n != NULL){
        int compare_result = compare(key, n->key);
        if(compare_result == 0){
            return n;
        } else if (compare_result > 0) {
            n = n->right;
        } else {
            n = n->left;
        }
    }
    return n;
}

void* bbst_lookup(bbst tree, void* key, compare_func compare){
    node n = lookup_node(tree, key, compare);
    return n == NULL ? NULL : n->value;
}

void rotate_right(bbst tree, node n){
    node pivot = n->left;
    replace_node(tree, n, pivot);
    n->left = pivot->right;
    if(pivot->right != NULL){
        pivot->right->parent = n;
    }
    pivot->right = n;
    n->parent = pivot;
}

void rotate_left(bbst tree, node n){
    node pivot = n->right;
    replace_node(tree, n, pivot);
    n->right = pivot->left;
    if(pivot->left != NULL){
        pivot->left->parent = n;
    }
    pivot->left = n;
    n->parent = pivot;
}

void replace_node(bbst tree, node old_node, node new_node){
    if(old_node->parent == NULL){
        tree->root = new_node;
    } else {
        if (old_node == old_node->parent->left)
            old_node->parent->left = new_node;
        else
            old_node->parent->right = new_node;
    }
    if(new_node != NULL)
        new_node->parent = old_node->parent;
}

void bbst_insert(bbst tree, void* key, void* value, compare_func compare){
    node inserted_node = new_node(key, value, RED, NULL, NULL);
    if(tree->root == NULL){
        tree->root = inserted_node;
    } else {
        node n = tree->root;
        while(1==1){
            int compare_result = compare(key, n->key);
            if(compare_result == 0){
                free(inserted_node);
                return;
            } else if (compare_result < 0) {
                if(n->left == NULL){
                    n->left = inserted_node;
                    break;
                } else
                    n = n->left;
            } else {
                if(n->right == NULL){
                    n->right = inserted_node;
                    break;
                } else
                    n = n->right;
            }
        }
        inserted_node->parent = n;
    }
    insert_case1(tree, inserted_node);
}

/* when n is root */
void insert_case1(bbst tree, node n){
    if (n->parent == NULL)
        n->color = BLACK;
    else
        insert_case2(tree, n);
}

/* when n is no root */
void insert_case2(bbst tree, node n){
    if (node_color(n->parent) == BLACK)
        return;
    else
        /* here n always have grandfather cuz he's RED */
        insert_case3(tree, n);
}

/* when uncle is red and parent is red and node itself is red */
void insert_case3(bbst tree, node n) {
    if (node_color(uncle(n)) == RED) {
        n->parent->color = BLACK;
        uncle(n)->color = BLACK;
        grandparent(n)->color = RED;
        insert_case1(tree, grandparent(n));
    } else {
        insert_case4(tree, n);
    }
}

/* when uncle is BLACK but parent is RED and node itself is RED but parent and node are different sides */
void insert_case4(bbst tree, node n) {
    if (n == n->parent->right && n->parent == grandparent(n)->left) {
        rotate_left(tree, n->parent);
        n = n->left;
    } else if (n == n->parent->left && n->parent == grandparent(n)->right) {
        rotate_right(tree, n->parent);
        n = n->right;
    }
    insert_case5(tree, n);
}

/* when uncle is BLACK but parent is RED and node itself is RED but parent and node are same side */
void insert_case5(bbst tree, node n) {
    n->parent->color = BLACK;
    grandparent(n)->color = RED;
    if (n == n->parent->left && n->parent == grandparent(n)->left) {
        rotate_right(tree, grandparent(n));
    } else {
        assert(n == n->parent->right && n->parent == grandparent(n)->right);
        rotate_left(tree, grandparent(n));
    }
}

void bbst_delete(bbst tree, void* key, compare_func compare) {
    node child;
    node n = lookup_node(tree, key, compare);
    if (n == NULL) return;
    if (n->left != NULL && n->right != NULL) {
        /* find the biggest of the lower */
        node predecessor = maximum_node(n->left);
        n->key           = predecessor->key;
        n->value         = predecessor->value;
        n                = predecessor;
    }

    assert(n->left == NULL || n->right == NULL);
    child = n->right == NULL ? n->left : n->right;
    if (node_color(n) == BLACK) {
        n->color = node_color(child);
        delete_case1(tree, n);
    }
    replace_node(tree, n, child);
    if (n->parent == NULL && child != NULL)
        child->color = BLACK;
    free(n);
}

static node maximum_node(node n) {
    assert (n != NULL);
    while (n->right != NULL) {
        n = n->right;
    }
    return n;
}

/*deleting the root node - everything is ok*/
void delete_case1(bbst tree, node n) {
    if (n->parent == NULL)
        return;
    else
        delete_case2(tree, n);
}

void delete_case2(bbst tree, node n) {
    if (node_color(sibling(n)) == RED) {
        n->parent->color = RED;
        sibling(n)->color = BLACK;
        if (n == n->parent->left)
            rotate_left(tree, n->parent);
        else
            rotate_right(tree, n->parent);
    }
    delete_case3(tree, n);
}

void delete_case3(bbst tree, node n) {
    if (node_color(n->parent) == BLACK &&
        node_color(sibling(n)) == BLACK &&
        node_color(sibling(n)->left) == BLACK &&
        node_color(sibling(n)->right) == BLACK)
    {
        sibling(n)->color = RED;
        delete_case1(tree, n->parent);
    }
    else
        delete_case4(tree, n);
}

void delete_case4(bbst tree, node n) {
    if (node_color(n->parent) == RED &&
        node_color(sibling(n)) == BLACK &&
        node_color(sibling(n)->left) == BLACK &&
        node_color(sibling(n)->right) == BLACK)
    {
        sibling(n)->color = RED;
        n->parent->color = BLACK;
    }
    else
        delete_case5(tree, n);
}

void delete_case5(bbst tree, node n) {
    if (n == n->parent->left &&
        node_color(sibling(n)) == BLACK &&
        node_color(sibling(n)->left) == RED &&
        node_color(sibling(n)->right) == BLACK)
    {
        sibling(n)->color = RED;
        sibling(n)->left->color = BLACK;
        rotate_right(tree, sibling(n));
    }
    else if (n == n->parent->right &&
             node_color(sibling(n)) == BLACK &&
             node_color(sibling(n)->right) == RED &&
             node_color(sibling(n)->left) == BLACK)
    {
        sibling(n)->color = RED;
        sibling(n)->right->color = BLACK;
        rotate_left(tree, sibling(n));
    }
    delete_case6(tree, n);
}

void delete_case6(bbst tree, node n) {
    sibling(n)->color = node_color(n->parent);
    n->parent->color = BLACK;
    if (n == n->parent->left) {
        assert (node_color(sibling(n)->right) == RED);
        sibling(n)->right->color = BLACK;
        rotate_left(tree, n->parent);
    }
    else
    {
        assert (node_color(sibling(n)->left) == RED);
        sibling(n)->left->color = BLACK;
        rotate_right(tree, n->parent);
    }
}
