// Online C compiler to run C program online
#include <stdio.h>

int main() {
    // Write C code here
    int a = 100;
    int b = 200;
//ptr1 is a constant pointer to an integer, so you can change the value it points to, but you cannot change the pointer itself.
    int * const ptr1 = &a;
    
//ptr2 is a pointer to a constant integer, so you can change the pointer to point to a different integer, but you cannot change the value of the integer it points to.
    int const * ptr2 = &b;
    
    *ptr1 = 500;
    // ptr1 = &b; // is commented out, but if it were executed, it would be invalid because ptr1 is a constant pointer and cannot be reassigned to point to b.
    
    ptr2 = &a;
    // *ptr2 = 500; // is commented out, but if it were executed, it would be invalid because ptr2 is a pointer to a constant integer, and you cannot change the value of the integer it points to through ptr2.

    return 0;
}
