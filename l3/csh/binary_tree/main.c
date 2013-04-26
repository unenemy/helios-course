#include <stdio.h>
#include <stdlib.h>
#include "bbst.h"

int compare_int(void* leftp, void* rightp){
    int left = (int)leftp;
    int right = (int)rightp;
    if(left < right)
        return -1;
    else if(left > right)
        return 1;
    else
        return 0;
}

void print_tree(bbst_node n){
    printf("%d left to %d\n", get_key(n->left), get_key(n));
    printf("%d right to %d\n", get_key(n->right), get_key(n));
    if(n->left != NULL) print_tree(n->left);
    if(n->right != NULL) print_tree(n->right);
}

int get_key(bbst_node n){
    return n == NULL ? 0 : (int)n->key;
}

int get_value(bbst_node n){
    return n == NULL ? 0 : (int)n->value;
}

int main()
{
    int i;
    bbst tree = bbst_create();
    for (i = 0; i < 10; i++) {
        int x = rand() % 100;
        int y = rand() % 100;
        bbst_insert(tree, (void*)x, (void*)y, compare_int);
        printf("\ninsetring %d(%d)\n", x, y);
        print_tree(tree->root);
    }
    return 0;
}
