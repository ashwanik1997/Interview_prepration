Interview Question prepration:

1. Write a program using funtion to return Maximum and Minimum numbers.

// Online C compiler to run C program online
#include <stdio.h>
int ret_max(int arr[], int size)
{
    int max = arr[0];
    for(int i=1 ; i< size; i++)
    {
        if(max < arr[i])
        {
            max = arr[i];
        }
    }
    return max;
}

int ret_min(int arr[], int size)
{
    int min = arr[0];
    for(int i = 0; i< size; i++)
    {
        if(min > arr[i])
        {
            min = arr[i];
        }
    }
    return min;
}
int main() {
    // Write C code here
    int size;
    printf("Input size of array : ");
    scanf("%d",&size);
    int array[size];
    for(int i = 0;i < size; i++)
    {
        scanf("%d",&array[i]);
    }
    
    printf("Maximum Number is : %d\r\n",ret_max(array,size));
    printf("Minimum Number is : %d\r\n",ret_min(array,size));
    
    return 0;
}

_____________________________________________________________________________

2. Implement Queue program using array. 

// Online C compiler to run C program online
//Max and min number

#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 10

int queue_arr[MAX_SIZE];
int rear = -1;
int front = -1;

void insert()
{
    int add_item;
    if(rear == MAX_SIZE -1)
    {
        printf("Queue Overflow \n");
    }
    else
    {
        if(front == -1)
        {
            front = 0;
        }
        printf("Insert the Element in Queue :");
        scanf("%d", &add_item);
        rear = rear + 1;
        queue_arr[rear] = add_item;
    }
}

void display()
{
    int i;
    if(front == -1)
    {
        printf("Queue is empty\r\n");
    }
    else
    {
        printf("Queue is :");
        for(i = front; i<= rear; i++)
        {
            printf("%d ",queue_arr[i]);
        }
        printf("\n");
    }
}
void delete()
{
    if(front == -1 || front > rear)
    {
        printf("Queue is underflow\r\n");
        return;
    }
    else
    {
        printf("Element deleted from queue is: %d\n", queue_arr[front]);
        front = front + 1;
    }
}
int main() {
    // Write C code here
    int choice;
    printf("1.Insert element to queue \r\n");
    printf("2.Delete element from queue \r\n");
    printf("3.Display all elements of queue \r\n");
    printf("4.Quit \r\n");
    
    while(1)
    {
        printf("Enter your choice :");
        scanf("%d",&choice);
        
        switch(choice)
        {
            case 1:
                insert();
                break;
            case 2:
                delete();
                break;
            case 3:
                display();
                break;
            case 4:
                printf("!! Quit !!");
                exit(1);
            default:
                printf("You have entered wrong input \r\n");
                
        }
    }
    
    return 0;
}
_____________________________________________________________________________

3. Write a program for Stack

// Online C compiler to run C program online
#include <stdio.h>

#define MAX 5
int top, status;

// Push Function
void push(int stack[], int item)
{
    if(top == (MAX -1))
    {
        status = 0;
    }
    else 
    {
        status = 1;
        ++top;
        stack[top] = item;
    }
}
//Pop Function
int pop(int stack[])
{
    int ret;
    if(top == -1)
    {
        ret = 0;
        status = 0;
    }
    else
    {
        status = 1;
        ret = stack[top];
        --top;
    }
    return ret;
}

//Function for Display element

void display(int stack[])
{
    int i;
    printf("\nThe Stack is :");
    if(top == -1)
    {
        printf(" Empty");
    }
    else
    {
        for(int i = top; i >= 0; --i)
        {
            printf("\n-------\n|%3d |\n-------",stack[i]);
        }
        printf("\n");
    }
}

int main()
{
    int stack[MAX];
    int item;
    int choice;
    top = -1;
    
    printf("\n1.Push Element in the Stack");
    printf("\n2.Pop Element from the Stack");
    printf("\n3.Exit");
    
    do{
        do
        {
            printf("\nEnter your Choice: ");
            scanf("%d", &choice);
            
            if(choice <1 || choice >3)
            {
                printf("Invalid Choice, Try again");
            }
        } while(choice <1 || choice >3);
        switch(choice)
        {
            case 1:
                printf("\nEnter the element to be Pushed :");
                scanf("%d",&item);
                printf("%d",item);
                push(stack, item);
                if(status)
                {
                    printf("\nAfter pushing ");
                    display(stack);
                    if(top ==(MAX -1))
                    {
                        printf("\nThe stack is Full");
                    }
                }
                else
                {
                    printf("Stack overflow on Push");
                }
                break;
            case 2:
                item = pop(stack);
                if(status)
                {
                    printf("\nThe Popped item os %d. After popping: ",item);
                    display(stack);
                }
                else
                {
                    printf("\nStack underflow on pop");
                }
                break;
            default:
                printf("\nEnd if execution");
        }
    } while (choice !=3);
    
    return 0;
}

_____________________________________________________________________________

4.
