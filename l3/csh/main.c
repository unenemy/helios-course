#include "stdio.h"
#include "stdlib.h"
#include "stdbool.h"
#include "list.h"
struct list_t* head=NULL;
struct list_t* curr=NULL;
void main(){
    head = curr = list_init('A');
    list_print(head);

    head = list_insert_front(head, 2);
    list_print(head);

    list_insert_after(head, 10, 0);
    list_insert_after(head, 11, 0);
    list_insert_after(head, 11, 4);
    list_print(head);
}
