#include "stdio.h"
#include "stdlib.h"
#include "stdbool.h"
#include "list.h"
struct list_t* head=NULL;
struct list_t* curr=NULL;
void main(){
    puts("init");
    head = curr = list_init();
    int a=1,b=2,c=3,x=5,d=12;
    list_print(head);
    list_insert_front(&head, &a);
    list_insert_front(&head, &b);
    list_print(head);

    list_insert_after(head, &c, 0);
    list_insert_after(head, &x, 0);
    list_insert_after(head, &x, 4);
    list_print(head);

    printf("%d is located at %d\n", d, search(head, &d));

    list_insert_rear(head, &d);
    list_print(head);

    printf("%d is located at %d\n", d, search(head, &d));

    list_remove_front(&head);
    list_remove_front(&head);
    list_print(head);

    list_remove_any(&head, &d);
    list_print(head);

    list_remove_rear(&head);
    list_print(head);
}
