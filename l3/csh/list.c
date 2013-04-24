#include "stdio.h"
#include "stdlib.h"
#include "stdbool.h"
#include "list.h"

struct list_t* list_init(){
    struct list_t *ptr = (struct list_t*)malloc(sizeof(struct list_t));
    if(NULL == ptr)
    {
        printf("\n Node creation failed \n");
        return NULL;
    }
    ptr->data = NULL;
    ptr->next = NULL;

    return ptr;
}

int list_size(struct list_t *head){
    int i=0;
    while(head != NULL && head->data != NULL){
        i++;
        head = head->next;
    }
    return i;
}

void list_print(struct list_t *head){
    struct list_t *ptr = head;
    int i = 0;
    if(list_size(head) == 0){
        printf("List is empty\n");
        return;
    }
    printf("\nList with size = %d contains:\n", list_size(head));
    while(NULL != ptr && NULL != ptr->data){
        printf("\t%d\t%d\n", i++, *(ptr->data));
        ptr = ptr->next;
        if(i>10)break;
    }
    return;
}

void list_insert_rear(struct list_t *head, int *data){
    list_insert_after(head, data, list_size(head)-1);
    return;
}

void list_insert_front(struct list_t* *head, int* data){
    if((*head)->data == NULL){
        (*head)->data = data;
        return;
    }
    struct list_t* ptr = (struct list_t*)malloc(sizeof(struct list_t));
    if(NULL == ptr)
    {
        return;
    }

    ptr->data = data;
    ptr->next = *head;
    *head = ptr;
    return;
}

void list_insert_after(struct list_t *head, int *data, int pos){
    struct list_t *ptr = (struct list_t*)malloc(sizeof(struct list_t));
    if(NULL == ptr || pos < 0 || list_size(head) <= pos)
    {
        printf("\nNode adding after %d failed \n", pos);
        return;
    }
    int i;
    for(i = 0; i < pos; i++)
        head = head->next;

    ptr->data = data;
    ptr->next = head->next;
    head->next = ptr;
    return;
}

void list_remove_front(struct list_t* *head){
    struct list_t *temp = (*head);
    if(list_size(*head) > 1){
        *head = temp->next;
        free(temp);
    } else {
        (*head)->data = NULL;
    }
}

void list_remove_rear(struct list_t* *head){
    struct list_t *prev = NULL;
    struct list_t *temp = *head;
    while(temp != NULL && temp->next != NULL){
        prev = temp;
        temp = temp->next;
    }
    if(temp != NULL){
        if(prev == NULL)
            list_remove_front(head);
        else{
            prev->next = temp->next;
            free(temp);
        }
    }
}

void list_remove_any(struct list_t* *head, int *data){
    struct list_t *prev = NULL;
    struct list_t *temp = *head;
    while(temp != NULL && temp->data != NULL && temp->data != data){
        prev = temp;
        temp = temp->next;
    }
    if(temp != NULL){
        if(prev == NULL)
            list_remove_front(head);
        else{
            prev->next = temp->next;
            free(temp);
        }
    }
}

int search(struct list_t *head, int *data){
    int i = 0;
    while(head != NULL){
        if(head->data == data)
            return i;
        head = head->next;
        i++;
    }
    return -1;
}
