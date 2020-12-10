#include <stdio.h>
#include <stdlib.h>
#include <string.h> //strlen,strcmp,strcat,strcpy and more ....

//there is no string type - instead of it You have to use char array
int length(char *str)
{
    int l = 0;
    while (*str++ != 0)
        l++; //*str points to the next character
    return l;
}
// **TODO** trim function (modify the length function so it skips the spaces in the beginning of the string)
int trimmedLength(char *str)
{
    int l = 0;
    while (*str++ != 0)
        if (*str != " ")
        {
            l++; 
        }
    return l;
}
int main()
{
    
    char str1[] = "Hello world";
    // the last character is a 0, signaling the end of the string
    // Length will be automatically calculated for the array 
    // char str[80]; would initialize an empty string 
    printf("The content of variable str1: \'%s\'\n", str1);
    // 1. parameter formatstring, next parameter(s) variables
        // %s = string, 
        // %i = integer 
        // \n = new line e.g.

    printf("The length of variable str1 \'%s\'\n  %i (with length()), %i (with strlen())\n", str1, length(str1), strlen(str1));
    // length is our own function, which doesn't count the end (0) character 
    // strlen does the same

    char *str2;  //it is a pointer variable (we have to allocate memory)
    str2 = str1; //the pointer shows to the same memory place
    printf("The content of variable str2 \'%s\' is the same as str1 \'%s\' \n(pointing the same memory place)\n", str2, str1);
    str2 = (char *)malloc(80 * sizeof(char)); 
    // no new operator in c
    // functions for allocating and freeing up memory
        // malloc -  allocates the requested memory and returns a pointer to it
            // void *malloc(size_t size)
        // realloc - attempts to resize the memory block pointed to by ptr that was previously allocated with a call to malloc or calloc
            // void *realloc(void *ptr, size_t size)
        // calloc - allocates the requested memory and returns a pointer to it. The difference in malloc and calloc is that malloc does not set the memory to zero where as calloc sets allocated memory to zero
            // void *calloc(size_t nitems, size_t size)
        // free - deallocates the memory previously allocated by a call to calloc, malloc, or realloc
            // void free(void *ptr)
    str2[0] = 'O'; //to write value character by character
    str2[1] = 'S';
    str2[2] = 0; //at the end of a string there has to be a 0 character!
    printf("We've given value character by character - str2: \'%s\'\n", str2); //new content

    strcpy(str2, "New content by using strcpy");
    // a value can be given with strcopy instead of doing it char by char
    printf("The new content of variable str2: \'%s\'\n", str2); //new content
    // important other functions (defined in string.h)
        // strcpy - copies the string pointed by source (including the null character) to the destination, and returns the copied string 
            // char* strcpy(char* destination, const char* source);
        // strcmp - compares two strings and returns 0 if both strings are identical
        // strcat - contcatenates (joins) two strings 
            // char *strcat(char *destination, const char *source)
            // result is stored in destination 
        // strlen - takes a string as an argument and returns its length
    free(str2);
    // allocated memory has to be freed
    return 0;
}
