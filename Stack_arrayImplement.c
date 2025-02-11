
//          ________  STACK____________

// Definition: A stack is a linear data structure in     which insertions and deletions are allowed only    at the end, called the top of the stack.
//          ___ Primary Stack Operations___
// PUSH(DATA): It allows to insert element to the stack
// POP() : It allow to remove the last inserted element in stack
// Top() : returns the last inserted element without removing it.
// Size() : reurns the size of stack 
// isEmpty() : returns TRUE if the stack is empty, else returns FALSE.
// isFull() : returns TRUE if the stack is full, else returns FALSE.
//          ___Array Implementations of Stacks__ 

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#define MAX    4
int top = -1;
int stack_arr[MAX];

bool isEmpty(void)
{
    if(top == -1)
        return true;
    else
        return false;
}
bool isFull(void)
{    
    if(top == MAX -1)
        return true;
    else
        return false;
}
void push(int data)
{
    if(isFull())
    {
        printf("\nStack Overflow");
        return;
    }
    top = top + 1;
    stack_arr[top] = data;
}
int pop(void)
{
    int temp;
    if(isEmpty())
    {
        printf("\r\nStack Underflow");
        exit(1);
    }
    temp = stack_arr[top];
    top = top - 1;
    return temp;
}

int Stack_size(void)
{
    return top+1;
}
void print_Stack(void)
{
    printf("\r\nElements in Stacks are");
    for(int i = top; i >= 0; i--)
    {
        printf("\n%d",stack_arr[i]);
    }
}

int main() {
    // Write C code here
    printf("Try programiz.pro");
    int data ;
    push(1);
    push(2);
    push(3);
    push(4);
    // push(5);
    print_Stack();
    data = pop();
    printf("\npop data = %d",data);
    data = pop();
    printf("\npop data = %d",data);
    print_Stack();
    printf("\nSize of stack = %d",Stack_size());
    return 0;
}
