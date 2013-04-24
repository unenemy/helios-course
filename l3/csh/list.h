struct list_t {
    int* data;
    struct list_t* next;
};

struct list_t* list_init();
void list_insert_front(struct list_t* *head, int *data);
void list_insert_rear(struct list_t *head, int *data);
void list_insert_after(struct list_t *head, int *data, int pos);
void list_remove_front(struct list_t* *head);
int list_size(struct list_t *head);
void list_print(struct list_t* head);
