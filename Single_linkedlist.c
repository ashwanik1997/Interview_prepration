// Online C compiler to run C program online


// DATA STRUCTURE IN C //
// SINGLE LINKED LIST PROGRAM //


#include <stdio.h>
#include <stdlib.h>
struct Node 
{
    int data;
    struct Node *next;
};
void count_of_nodes(struct Node * head);
void print_node_data(struct Node * head);
void insert_at_first(struct Node ** head, int data);
void insert_at_end(struct Node * head, int data);
void insert_at_pos(struct Node** head, int pos, int data);
struct Node * delete_first_node(struct Node * head);
struct Node * delete_last_node(struct Node * head);
void delete_at_pos(struct Node ** head, int pos);
struct Node * delete_single_linklist(struct Node *head);
struct Node * reverse_list(struct Node *head);
int main() {
    // Write C code here
    struct Node *head = NULL;
    head = (struct Node *) malloc(sizeof(struct node *)); 
    head-> data = 10;
    head-> next = NULL;
    
    struct Node * ptr2 = (struct Node *) malloc(sizeof(struct node *)); 
    ptr2-> data = 20;
    ptr2-> next = NULL;
    
    head->next = ptr2;
    
    ptr2 = malloc(sizeof(struct node *)); 
    ptr2-> data = 30;
    ptr2-> next = NULL;

    head-> next ->next = ptr2;
    
    count_of_nodes(head);
    print_node_data(head);
    insert_at_end(head, 40);
    print_node_data(head);
    insert_at_first(&head, 5);
    print_node_data(head);
    count_of_nodes(head);
    insert_at_pos(&head, 2, 25);
    print_node_data(head);
    count_of_nodes(head);
    head = delete_first_node(head);
    count_of_nodes(head);
    print_node_data(head);
    delete_at_pos(&head, 2);
    count_of_nodes(head);
    print_node_data(head);
    // printf("\r\ncalling delete_single_linklist\r\n");
    // head = delete_single_linklist(head);
    // print_node_data(head);
    head = reverse_list(head);
    print_node_data(head);
    return 0;
}

void count_of_nodes(struct Node * head)
{
    int count = 0;
    if(head == NULL)
        printf("Linked list is empty\n");
    struct Node * ptr = NULL;
    ptr = head;
    while( ptr != NULL)
    {
        count ++;
        ptr = ptr -> next;
    }
    printf("No. of Node : %d\r\n", count);
    
}
void print_node_data(struct Node * head)
{
    if(head == NULL)
        printf("Linked list is empty\r\n");
    struct Node * ptr = NULL;
    ptr = head;
    while(ptr != NULL)
    {
        printf("%d  ",ptr->data);
        ptr = ptr -> next;
    }
    printf("\n");
}
void insert_at_first(struct Node ** head, int data)
{
    struct Node *temp = (struct Node *)malloc(sizeof(struct Node *));
    temp ->data = data;
    temp ->next = NULL;
    
    temp-> next = *head;
    *head = temp;
}
void insert_at_end(struct Node * head, int data)
{
    struct Node *ptr, *temp;
    ptr = head;
    temp = (struct Node *) malloc(sizeof(struct node *));
    temp-> data = data;
    temp-> next = NULL;
    
    while(ptr->next !=NULL)
    {
        ptr = ptr-> next;
    }
    ptr-> next = temp;
}

// Function to insert a node at a specific position
void insert_at_pos(struct Node** head, int pos, int data) {
    // Create a new node
    struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));
    new_node->data = data;

    // If inserting at the head (position 0)
    if (pos == 0) 
    {
        new_node->next = *head;
        *head = new_node;
        return;
    }
    // Traverse to the node just before the desired position
    struct Node* temp = *head;
    int current_pos = 0;

    while (temp != NULL && current_pos < pos - 1) 
    {
        temp = temp->next;
        current_pos++;
    }

    // If the position is out of bounds
    if (temp == NULL) 
    {
        printf("Invalid position\n");
        free(new_node);
        return;
    }

    // Insert the new node at the desired position
    new_node->next = temp->next;
    temp->next = new_node;
}
void add_at_pos(struct Node * head, int pos, int data)
{
    struct Node * ptr = head;
    struct Node *ptr2 = malloc(sizeof(struct Node *));
    ptr2-> data = data;
    ptr2-> next = NULL;
    
    pos--;
    while(pos != 1)
    {
        ptr = ptr->next;
        pos--;
    }
    ptr2-> next = ptr-> next;
    ptr-> next = ptr2;
}

struct Node * delete_first_node(struct Node * head)
{
    if(head == NULL)
    {
        printf("\r\nList is already Empty");
    }
    else
    {
        struct Node * temp = head;
        head = head-> next;
        free(temp);
        temp = NULL;
    }
    return head;
}

struct Node * delete_last_node(struct Node * head)
{
    if(head == NULL)
    {
        printf("\nList is already empty");
    }
    else if(head-> next == NULL)
    {
        free(head);
        head = NULL;
    }
    else
    {
        struct Node * temp = head;
        struct Node * temp2 = head;
        while(temp->next != NULL)
        {
            temp2 = temp;
            temp = temp-> next;
        }
        temp2-> next = NULL;
        free(temp);
        temp = NULL;
    }
    return head;
}

void delete_at_pos(struct Node ** head, int pos)
{
    struct Node * curr = *head;
    struct Node * prev = * head;
    if(*head == NULL)
    {
        printf("\r\nList is already empty");
    }
    else if (pos == 1)
    {
        *head = curr-> next;
        free(curr);
        curr = NULL;
    }
    else
    {
        while(pos != 1)
        {
            prev = curr;
            curr = curr-> next;
            pos--;
        }
        prev-> next = curr-> next;
        free(curr);
        curr = NULL;
    }
}
struct Node * delete_single_linklist(struct Node *head)
{
    struct Node * temp  = head;
    while(temp != NULL)
    {
        temp = temp-> next;
        free(head);
        head = temp;
    }
    return head;
}
struct Node * reverse_list(struct Node *head)
{
    struct Node * Prev = NULL;
    struct Node * Next = NULL;
    
    while(head != NULL)
    {
        Next = head-> next;
        head-> next = Prev;
        Prev = head;
        head = Next;
    }
    head = Prev;
    return head;
}
