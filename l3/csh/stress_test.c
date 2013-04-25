#include "stdio.h"
#include "stdlib.h"
#include "stdbool.h"
#include "list.h"
struct list_t* head=NULL;
void main(){
    puts("init stress");
    head = list_init();
    int i;
    for (i = 0; i < 100000; i++) {
        list_insert_rear(&head, &i);
    }
    list_print(head);
    for (i = 0; i < 100000; i++) {
        list_remove_front(&head);
    }
    free(head);

}
