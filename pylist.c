#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node *left;
    struct Node *right;
};

struct Node *head = NULL;
struct Node *tail = NULL;
int length = 0;

struct Node* get_node()
{
    return (struct Node*) malloc(sizeof(struct Node));
}

struct Node* reach_pos(int pos)
{
    struct Node *ptr;
    if (pos > 0)
    {
        ptr = head;
        while (pos != 0)
        {
            ptr = ptr->right;
            pos--;
        }
        return ptr->left;
    }
    
    ptr = tail;
    while (pos != -1)
    {
        ptr = ptr->left;
        pos++;
    }
    return ptr->left;
}

void insert_first(int value)
{
    struct Node *new = get_node();
    new->data = value;
    if (head == NULL)
    {    
        new->right = NULL;
        tail = new;        
    }
    else
    {
        new->right = head;
        head->left = new;
    }
    new->left = NULL;
    head = new;    
}

void insert_last(int value)
{
    struct Node *new = get_node();
    new->data = value;
    
    if (head == NULL)
    {
        new->left = NULL;
        head = new;
    }
    else 
    {
        new->left = tail;
        tail->right = new;
    }
    new->right = NULL;
    tail = new;
}

void insert(int pos, int value)
{
    if (pos == 0 || pos < 0-length) 
    {
        insert_first(value);
        length++;
        return;
    }
    else if (pos == -1 || pos >= length)
    {
        insert_last(value);
        length++;
        return;
    }
    
    struct Node *new, *l, *r;
    new = get_node();
    new->data = value;

    l = reach_pos(pos);
    r = l->right;
    new->left = l;
    new->right = r;
    l->right = r->left = new;
    length++;
}

void del_first()
{
    struct Node *ptr = head;
    head = head->right;
    head->left = NULL;
    free(ptr);
}

void del_last()
{
    struct Node *ptr = tail;
    tail = tail->left;
    tail->right = NULL;
    free(ptr);
}

void del(int pos)
{
    if (pos >= length || pos < 0-length)
    {
        printf("IndexError: list index %d out of range\n", pos);
        return;
    }
    else if (pos == 0 || pos == 0-length)
    {
        del_first();
        length--;
        return;
    }
    else if (pos == -1 || pos == length-1)
    {
        del_last();
        length--;
        return;
    }

    struct Node *l, *x, *r;
    l = reach_pos(pos);
    x = l->right;
    r = x->right;
    l->right = r; 
    r->left = l;
    free(x);
    length--;
}

void print_pylist()
{   
    struct Node *ptr = head;
    printf("[");
    while (ptr != NULL)
    {
        // printf("left=%d, data=%d, right=%d\n", ptr->left, ptr->data, ptr->right);
        printf("%d", ptr->data);
        ptr = ptr->right;
        if (ptr != NULL)
           printf(", ");
    }
    printf("]\n");
}

void main()
{
    print_pylist();
    insert(-1, 10);
    insert(0, 14);
    insert(0, 45);
    insert(-1, 20);
    insert(2, 13);
    insert(-6, 67);
    insert(5, 27);
    insert(9, 90);
    insert(-11, 110);
    print_pylist();
    del(3);
    print_pylist(); 
    del(-4);
    print_pylist();
}
