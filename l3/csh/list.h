struct list_t {
    int data;
    struct list_t* next;
};

struct list_t* list_init(int data);
struct list_t* list_insert_front(struct list_t *head, int data);
struct list_t* list_insert_after(struct list_t *head, int data, int pos);
int list_size(struct list_t *head);
void list_print(struct list_t* head);
