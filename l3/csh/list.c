#include "stdio.h"
#include "stdlib.h"
#include "stdbool.h"
#include "list.h"

struct list_t* list_init(int data){
    printf("\nCreating list with head value %d\n",data);
    struct list_t *ptr = (struct list_t*)malloc(sizeof(struct list_t));
    if(NULL == ptr)
    {
        printf("\n Node creation failed \n");
        return NULL;
    }
    ptr->data = data;
    ptr->next = NULL;

    return ptr;
}

struct list_t* list_insert_front(struct list_t *head, int data){
    struct list_t *ptr = (struct list_t*)malloc(sizeof(struct list_t));
    if(NULL == ptr)
    {
        return NULL;
    }

    printf("adding before %d\n", head->data);
    ptr->data = data;
    ptr->next = head;
    head = ptr;

    return head;
}

struct list_t* list_insert_after(struct list_t *head, int data, int pos){
    struct list_t *ptr = (struct list_t*)malloc(sizeof(struct list_t));
    if(NULL == ptr || pos < 0 || list_size(head) <= pos)
    {
        printf("\nNode adding after %d failed \n", pos);
        return NULL;
    }
    int i;
    for(i = 0; i < pos; i++)
        head = head->next;

    ptr->data = data;
    ptr->next = head->next;
    head->next = ptr;

    return head;
}

int list_size(struct list_t *head){
    int i = 0;
    while(NULL != head){
        i++;
        head = head->next;
    }
    return i;
}

void list_print(struct list_t* head){
    struct list_t *ptr = head;
    int i = 0;
    printf("\nList with size = %d contains:\n", list_size(head));
    while(ptr != NULL){
        printf("\t%d\t%d\n", i++, ptr->data);
        ptr = ptr->next;
        if(i>10)break;
    }
    return;
}
