/******************************************************************************
*file: singly_linkedlist.c
*author: Ashwani Kesharwani
*about: Singly Linked List Implementation
*******************************************************************************/
#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node *link;
};

void DisplayNode(struct Node* head)
{
    if(head == NULL)
    {
        printf("Node is Empty\n");
    }
    else
    {
        struct Node* ptr = head;
        while(ptr != NULL)
        {
            printf("%d-> ",ptr -> data);
            ptr = ptr-> link;
        }
        printf("NULL\n");
    }
}

int countNode(struct Node* head)
{
    int count = 0;
    struct Node *ptr = head;
    while(ptr != NULL)
    {
        count++;
        ptr = ptr-> link;
    }
    return count;
}

struct Node *createNode (int data)
{
    struct Node* cluster = (struct Node*) malloc(sizeof(struct Node));
    cluster->data = data;
    cluster-> link = NULL;
    return cluster;
}

struct Node *InsertBeg(struct Node* head, int data)
{
    struct Node * temp = createNode(data);
    temp-> link = head;
    head = temp;
    return head;
}

struct Node* InsertLast(struct Node* head, int data)
{
    struct Node *temp = createNode(data);
    
    if(head == NULL)
    {
        head = temp;
        return head;
    }
    
    struct Node *ptr = head;
    
    while(ptr-> link != NULL)
    {
        ptr = ptr-> link;
    }
    ptr-> link = temp;
    return head;
}

struct Node *InsertPos(struct Node* head, int pos, int data)
{
    struct Node *temp = createNode(data);
    struct Node *ptr = head;
    if(pos <= 0)
    {
        printf("Invalid position: %d\n", pos);
        free(temp);
        temp = NULL;
        return head;
    }
    else if(pos == 1)
    {
        temp-> link = head;
        head = temp;
        return head;
    }
    
    for(int i=1; i< pos -1 && ptr != NULL; i++)
    {
        ptr = ptr-> link;
    }
    if(ptr == NULL)
    {
        printf("Position is out of context");
        free(temp);
        temp = NULL;
        return head;
    }
    temp-> link = ptr-> link;
    ptr-> link = temp;
    return head;
}

struct Node* InsertPosfromLast(struct Node* head, int pos, int data)
{
    struct Node* temp = createNode(data);
    int loc = countNode(head) - pos;
    
    if(loc <= 0 ||loc < 0 || loc > countNode(head))
    {
        printf("Invalid position : %d\n",pos);
        free(temp);
        temp = NULL;
        return head;
    }
    if(loc == 0)
    {
        temp-> link = head;
        head = temp;
        return head;
    }
    struct Node* ptr = head;
    for(int i = 0; i < loc && ptr != NULL; i++)
    {
        ptr = ptr-> link;
    }
    temp-> link = ptr-> link;
    ptr-> link = temp;
    return head;
}

struct Node* ReverseListRecursively(struct Node* head)
{
    if(head == NULL || head -> link == NULL )
    {
        return head;
    }
    struct Node* ptr = ReverseListRecursively(head-> link);
    head-> link -> link = head;
    head-> link = NULL;
    return ptr;
}

struct Node* ReverseList(struct Node* head)
{
    if(head == NULL)
    {
        printf("list is Empty\n");
        return head;
    }
    struct Node* curr = head;
    struct Node* prev = NULL;
    struct Node* next = NULL;
    while(curr != NULL)
    {
        next = curr-> link;
        curr-> link = prev;
        prev = curr;
        curr = next;
    }
    head = prev;
    return head;
}

struct Node* DeleteBeg(struct Node* head)
{
    if(head == NULL)
    {
        printf("List is Empty\n");
        return NULL;
    }
    else
    {
        struct Node * ptr = head;
        head = head -> link;
        free(ptr);
        ptr = NULL;
        return head;
    }
}

struct Node* DeleteLast(struct Node * head)
{
    if(head == NULL)
    {
        printf("List is Empty");
        return NULL;
    }
    if(head -> link == NULL)
    {
        free(head);
        head = NULL;
        return head;
    }

    struct Node * ptr = head;
    struct Node * last;
    while(ptr-> link-> link != NULL)
    {
        ptr = ptr -> link;
    }
    last = ptr-> link;
    ptr-> link = NULL;
    free(last);
    last = NULL;
    return head;
    
}

struct Node * DeletePos(struct Node* head, int pos)
{
    if(head == NULL || pos <= 0)
    {
        printf("List is already Empty or Invalid Position\n");
        return head;
    }
    struct Node * ptr = head;
    if(pos == 1)
    {
        head = head -> link;
        free(ptr);
        ptr = NULL;
        return head;
    }
    
    for(int i = 1; i < pos -1 && ptr != NULL ; i++)
    {
        ptr = ptr-> link;
    }
    if(ptr == NULL || ptr-> link == NULL)
    {
        printf("Invalid Position");
        return head;
    }
    
    struct Node * ptr2 = ptr-> link;
    ptr -> link = ptr2 -> link;
    free(ptr2);
    ptr2 = NULL;
    return head;
}

struct Node* DeletePosfromLast(struct Node *head, int pos)
{
    if(head == NULL)
    {
        printf("List is Empty\n");
        return head;
    }
    
    int loc = countNode(head) - pos;
    
    if(loc <= 0 || loc > countNode(head))
    {
        printf("Invalid Position");
        return head;
    }
  
    if(loc == 1)
    {
        struct Node * temp = head;
        head = head -> link;
        free(temp);
        temp = NULL;
        return head;
    }
    
    struct Node * ptr = head;
    for(int i = 1; i < loc -1 && ptr != NULL ; i++)
    {
        ptr = ptr -> link;
    }
    
    if(ptr == NULL || ptr-> link == NULL)
    {
        printf("Invalid Position\n"); 
        return head;
    }
    struct Node * temp = ptr -> link;
    ptr-> link = temp -> link;
    free(temp);
    temp = NULL;
    return head;
}

struct Node* InsertionSort(struct Node* head)
{
    struct Node* sorted = NULL;
    while(head != NULL)
    {
        struct Node * current = head;
        head = head -> link;
        
        if(sorted == NULL || sorted-> data >= current -> data)
        {
            current-> link = sorted;
            sorted = current;
        }
        else
        {
            struct Node* temp = sorted;
            while(temp-> link != NULL && temp-> link-> data < current -> data)
            {
                temp = temp -> link;
            }
            current-> link = temp -> link;
            temp-> link = current;
        }
    }
    return sorted;
}

struct Node* BubbleSort(struct Node* head)
{
    if(head == NULL)
    {
        printf("List is Empty\n");
        return head;
    }
    
    int swapped;
    struct Node * ptr;
    struct Node * last = NULL;
    do {
        swapped = 0;
        ptr = head;
        
        while(ptr-> link != last)
        {
            if(ptr-> data > ptr->link -> data)
            {
                int temp = ptr-> data;
                ptr-> data = ptr-> link-> data;
                ptr-> link -> data = temp;
                swapped = 1;
            }
            ptr = ptr-> link;
        }
        last = ptr;
    }while(swapped);
    
    return head;
}

int main() {
    struct Node* head = NULL;

    printf("Inserting at the beginning...\n");
    head = InsertBeg(head, 20);
    head = InsertBeg(head, 30);
    head = InsertBeg(head, 10);
    head = InsertBeg(head, 45);
    head = InsertBeg(head, 40);
    
    DisplayNode(head);
    
    printf("Bubble Sorting...\n");
    head = BubbleSort(head);
    DisplayNode(head);

    printf("Inserting at the end...\n");
    head = InsertLast(head, 10);
    DisplayNode(head);

    printf("Inserting at position 2...\n");
    head = InsertPos(head, 2, 35);
    DisplayNode(head);

    printf("Number of nodes: %d\n", countNode(head));
    
    printf("Inserting at position 3 from last...\n");
    head = InsertPosfromLast(head, 3, 25);
    DisplayNode(head);
    
    printf("Reverse List Recursively....\n");
    head = ReverseListRecursively(head);
    DisplayNode(head);
    
    printf("Reverse List...\n");
    head = ReverseList(head);
    DisplayNode(head);
    
    printf("Deleting at the beginning...\n");
    head = DeleteBeg(head);
    DisplayNode(head);
    
    printf("Deleting at the Last...\n");
    head = DeleteLast(head);
    DisplayNode(head);
    
    printf("Deleting at the position...\n");
    head = DeletePos(head, 2);
    DisplayNode(head);
    
    printf("Deleting at the position from last...\n");
    head = DeletePosfromLast(head, 2);
    DisplayNode(head);
    
    printf("Insertion Sorting...\n");
    head = InsertionSort(head);
    DisplayNode(head);
    
    return 0;
}
