#include <stdio.h>
#include <cs50.h>

int  main(void) 
{
    string name = get_string("what's your name? "); //asks for user name
    printf("hello, %s\n", name); //prints hello, username
}