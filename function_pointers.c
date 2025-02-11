/*
Function pointers are an advanced feature in C programming that allow you to store the address of a function in a pointer variable. They enable flexible and efficient code, especially useful for callbacks, dynamic function calls, and implementing state machines. 
*/
#include <stdio.h>

void greet(const char * name)
{
    printf("Hello %s",name);
}
void add( int a, int b)
{
    printf("Addition of a+b = %d\r\n", a+b);
}
void sub( int a, int b)
{
    printf("Subtraction of a-b = %d\r\n", a-b);
}
void mul( int a, int b)
{
    printf("Multiplication of a*b = %d\r\n", a*b);
}
void div( int a, int b)
{
    printf("Divition of a/b = %d\r\n", a/b);
}

//simple function pointer which takes two arguments
void (*execute)(int , int );

//Function as arguments
void operation(void (*callback)(int, int ), int a, int b)
{
    callback(a, b);
}

//Function as arguments
void caller( void (*callback) (const char *), const char * arg)
{
    callback(arg);
}

void state_A(void)
{
    printf("State A Called\r\n");
}
void state_B(void)
{
    printf("State B Called\r\n");
}
void state_C(void)
{
    printf("State C Called\r\n");
}

int main() {
    // Write C code here
	
    caller(greet, "Ashwani");
    printf("\r\n");
    
    //Array of Function Pointers 
    void (*State[])(void) = {state_A, state_B, state_C};
    // Simulating state transitions
    for (int i = 0; i < 3; i++)
    {
        State[i]();
    }
    
	
    execute = &add;
    execute(10, 20);
    execute = &sub;
    execute(40, 20);
    execute = &mul;
    execute(10, 20);
    execute = &div;
    execute(200, 20);
    
	//Function passed ass arguments
    operation(add,10, 20);
    operation(sub,30, 20);
    operation(mul,10, 10);
    operation(div,100, 20);
    return 0;
}
