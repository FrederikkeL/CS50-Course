#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int stairHeigth;
    do
    {
        stairHeigth = get_int("Height: ");
    }
    while (stairHeigth > 8 || stairHeigth <= 0);

    for (int i = 1; i <= stairHeigth; i++)
    {
        // prints first columns spaces
        for (int k = stairHeigth - i; k > 0; k--)
        {
            printf(" ");
        }
        // prints first columns #
        for (int l = 0; l < i; l++)
        {
            printf("#");
        }
        // prints middle spaces
        printf("  ");

        // prints second columns
        for (int j = 0; j < i; j++)
        {
            printf("#");
        }

        printf("\n");
    }
}