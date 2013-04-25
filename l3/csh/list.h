struct list_t {
    void* data;
    struct list_t* next;
};

struct list_t* list_init();
void list_insert_front(struct list_t* *head, void *data);
void list_insert_rear(struct list_t* *head, void *data);
void list_insert_after(struct list_t *head, void *data, int pos);
void list_remove_front(struct list_t* *head);
void list_remove_rear(struct list_t* *head);
void list_remove_any(struct list_t* *head, void *data);
int search(struct list_t *head, void *data);
int list_size(struct list_t *head);
void list_print(struct list_t* head);
