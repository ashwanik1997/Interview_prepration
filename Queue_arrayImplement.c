// Online C compiler to run C program online
/*
Definition: A Queue Data Structure is a fundamental concept in computer science used for storing and managing data in a specific order. It follows the principle of "First in, First out" (FIFO), where the first element added to the queue is the first one to be removed. Queues are commonly used in various algorithms and applications for their simplicity and efficiency in managing data flow.

*/
#include <stdio.h>
#define SIZE    5

int queue[SIZE];
int front = -1;
int rear = -1;

void enqueue (int data);
void dequeue (void);
void display (void);

int main() {
    // Write C code here
    enqueue(10);
    enqueue(20);
    enqueue(30);
    enqueue(40);
    enqueue(50);
    // enqueue(60);
    display();
    dequeue();
    display();
    dequeue();
    display();

    return 0;
}

void enqueue (int data)
{
    if(rear == SIZE -1)
    {
        printf("Queue Overflow\n");
        exit(1);
    }
    else
    {
        if(front == -1)
        {
            front = 0;
        }
        rear++;
        queue[rear] = data;
    }
}
void dequeue (void)
{
    if(front == -1 || front > rear)
    {
        printf("\nQueue Underflow");
    }
    else 
    {
        printf("\nDequeued: %d",queue[front]);
        for (int i = 0; i < rear ; i++) {
            queue[i] = queue[i + 1];
        }
        // decrement rear
        rear--;
    }
    return;
}
void display (void)
{
    if(front == -1)
    {
        printf("\nQueue is Empty");
    }
    else
    {
        printf("\nElements are: ");
        for(int i = 0; i <= rear; i++)
        {
            printf(" %d  ",queue[i]);
        }
    }
}
