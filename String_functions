/*
*********************************************************************
* @file String_Function
* @author Ashwani Kesharwani
* @brife String function implementation
* @include  <string.h>
*
**********************************************************************
*/

#include <stdio.h>
#include <string.h>

int main()
{
    char arr[10] = "AshwaniK";
    char strcpyf[20];
    char strncpyf[20];
    char strcatf[20];
    char strncatf[20] = "Hello,";
    const char * strchrf = "Hello world!";
    char ch = 'o';
    char *result;
    const char *strstrf = "My dear hello sir and hello mam";
    const char *needle = "hello";
    char strtokf[] = "Hello, world! Welcome to C classes";
    const char delim[] = " ,.!";
    char *token;
    
/*strlen:
Prototype: size_t strlen(const char *str);
Description: Returns the length of the string str (excluding the null terminator).*/
    
    printf("Strlen : %ld\n",(size_t)strlen(arr));
    
/*strcpy:
Prototype: char *strcpy(char *dest, const char *src);
Description: Copies the string src to dest (including the null terminator).*/
  
    strcpy(strcpyf, arr);
    printf("strcpyf: %s\n",strcpyf);

/*strncpy:
Prototype: char *strncpy(char *dest, const char *src, size_t n);
Description: Copies up to n characters from the string src to dest. If src is less 
than n characters long, the remainder of dest is filled with null characters.*/
    
    strncpy(strncpyf, arr, 7);
    printf("strncpyf: %s\n",strncpyf);
    
/*strcat:
Prototype: char *strcat(char *dest, const char *src);
Description: Appends the string src to the end of dest (including the null terminator).*/

    strcat(strcatf, "Hello ");
    strcat(strcatf, arr);
    printf("strcatf: %s\n",strcatf);
    
/*strncat:
Prototype: char *strncat(char *dest, const char *src, size_t n);
Description: Appends up to n characters from the string src to the end of dest, 
and then adds a null terminator.*/

    strncat(strncatf, " World! Welcome to C classed ", 6);
    printf("strncatf: %s\n",strncatf);
    
/*strcmp:

Prototype: int strcmp(const char *str1, const char *str2);
Description: Compares the string str1 to str2. Returns an integer less than, equal to, 
or greater than zero if str1 is found to be less than, to match, or be greater than str2, respectively.*/
    
    printf("strcmp : %d\n", strcmp(strcpyf, arr));

/*strncmp:
Prototype: int strncmp(const char *str1, const char *str2, size_t n);
Description: Compares up to n characters of the string str1 to str2.*/
    
    printf("strncmp : %d\n", strncmp(strcpyf, arr, 10));

/*strchr:
Prototype: char *strchr(const char *str, int c);
Description: Returns a pointer to the first occurrence of the character c in the 
string str, or NULL if the character is not found.*/
    
    result = strchr(strchrf, ch);
    if(result != NULL){
        printf("strchrf: Char '%c' found at pos: %ld\n", ch, result -strchrf);
    } else {
        printf("strchrf: Char '%c' not found. \n",ch);
    }
    
/*strrchr:
Prototype: char *strrchr(const char *str, int c);
Description: Returns a pointer to the last occurrence of the character c in the string
 str, or NULL if the character is not found.*/
    
    result = strrchr(strchrf, ch);
    if(result != NULL){
        printf("strrchrf: Char '%c' found at pos: %ld\n", ch, result -strchrf);
    } else {
        printf("strrchrf: Char '%c' not found. \n",ch);
    }
    
/*strstr:
Prototype: char *strstr(const char *haystack, const char *needle);
Description: Returns a pointer to the first occurrence of the substring needle in the
 string haystack, or NULL if the substring is not found.*/
    
    result = strstr(strstrf, needle);
    if(result != NULL){
    printf("strstrf: string '%s' found at pos: %ld\n", needle, result - strstrf);
    } else {
        printf("strstrf: string '%s' not found. \n",needle);
    }
    
/*strtok:
Prototype: char *strtok(char *str, const char *delim);
Description: Breaks the string str into a series of tokens separated by the characters in delim.*/
    
    token = strtok(strtokf, delim);
    while(token != NULL)
    {
        printf("Token: %s\n", token);
        token = strtok(NULL, delim);
    }
    return 0;
}
