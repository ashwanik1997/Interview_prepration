// Online C compiler to run C program online
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

int main() {
    // Write C code here
    int guess;
    srand(time(0));
    int random_number = (rand() % 100) + 1;
    do
    {
        printf("\ninput your Number : ");
        scanf("%d",&guess);
        if(abs(guess - random_number) <= 5)
        {
            if(random_number != guess)
            {
                printf("You are near to that number");
            }
            else
            {
                printf("\nThat's correct, Congrats !!");
            }    
        }
        else if(random_number > guess)
        {
            printf("It's too low");
        }
        else
        {
            printf("It's too high");            
        }
        
    }while(random_number != guess);
    return 0;
}
