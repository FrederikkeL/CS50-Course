#include <cs50.h>
#include <stdio.h>

int main(void)
{
    long creditCardNumber = get_long("Credit card no.:"); // asks for creditCardNumber card no
    int totalSum = 0;
    long digitsLeft = creditCardNumber;
    while (creditCardNumber >= 1)
    {
        long lastDigit = creditCardNumber % 10;
        long rest = creditCardNumber / 10;
        long everyOther = rest % 10;
        creditCardNumber = creditCardNumber / 100; 

        long product = everyOther * 2;
        long productLastDigit = product % 10;    
        long productFirstDigit = product / 10; 
        totalSum = totalSum + productLastDigit + productFirstDigit + lastDigit;
    }

    int digitCount = 2; 
    // Count starts at two, since the loop stops when there are 2 digits left
    while (digitsLeft > 99)
    {
        digitsLeft = digitsLeft / 10;
        digitCount++;
    }

    int controlDigit = totalSum % 10;
    if (controlDigit == 0)
    {
        if (digitsLeft / 10 == (int)4 && (digitCount == 13 || digitCount == 16))
        {
            printf("VISA\n");
        }
        else if ((digitsLeft >= 51 && digitsLeft <= 55) && digitCount == 16)
        {
            printf("MASTERCARD\n"); 
        }
        else if ((digitsLeft == 34 || digitsLeft == 37) && digitCount == 15)
        {
            printf("AMEX\n"); 
        }
        else
        {
            printf("INVALID\n"); 
        }
    }
    else
    {
        printf("INVALID\n");
    }
}