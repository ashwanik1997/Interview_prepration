// Online C compiler to run C program online
/*
    Circular Buffer, circular queue, ring buffer
*/

#include <stdio.h>

#define BUFFER_SIZE 6
int head = 0;
int tail = 0;
int isFull_Flag = 0;
int CircularBuffer[BUFFER_SIZE];
int is_BufferFull(void)
{
    return isFull_Flag;
}
int is_BufferEmpty(void)
{
    int temp = 0;
    
    if((head == tail) && (isFull_Flag != 1))
    {
        temp = 1;
    }
    return temp;
}

void Status(void)
{
    printf("\nHead = %d    Tail = %d    isFull_Flag = %d", head, tail, isFull_Flag);
}

void WritetoBuffer(int data_element)
{
    if(is_BufferFull())
    {
        printf("\nBuffer is Full");
    }
    else
    {
        CircularBuffer[head] = data_element;
        printf("\nWrite to Buffer: %d",CircularBuffer[head]);
        head = (head + 1) % BUFFER_SIZE;
        if(head == tail)
        {
            isFull_Flag = 1;
        }
    }
}

void ReadfromBuffer(int * data_element)
{
    if(is_BufferEmpty())
    {
        printf("\nBuffer is Empty");
    }
    else
    {
        *data_element = CircularBuffer[tail];
        printf("\nRead from Buffer: %d",CircularBuffer[tail]);
        tail = (tail + 1) % BUFFER_SIZE;
        isFull_Flag = 0;
    }
}

int main() {
    // Write C code here
    int cnt;
    ReadfromBuffer(&cnt);
    Status();
    WritetoBuffer(10);
    Status();
    WritetoBuffer(20);
    Status();
    WritetoBuffer(30);
    Status();
    WritetoBuffer(40);
    Status();
    WritetoBuffer(50);
    Status();
    WritetoBuffer(60);
    Status();
    ReadfromBuffer(&cnt);
    Status();
    ReadfromBuffer(&cnt);
    Status();
    ReadfromBuffer(&cnt);
    Status();
    return 0;
}
