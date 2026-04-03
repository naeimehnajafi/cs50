#include <cs50.h>
#include <stdio.h>

int main(void)
{
    long number = get_long("Number: ");

    int sum = 0;
    int count = 0;
    long temp = number;

    while (temp > 0)
    {
        int digit = temp % 10;
        temp /= 10;
        count++;

        if (count % 2 == 0)
        {
            digit *= 2;
            if (digit > 9)
            {
                digit = digit % 10 + digit / 10;
            }
        }
        sum += digit;
    }

    if (sum % 10 != 0)
    {
        printf("INVALID\n");
        return 0;
    }

    long first_two = number;
    while (first_two >= 100)
    {
        first_two /= 10;
    }

    long first_one = first_two / 10;

    if (count == 15 && (first_two == 34 || first_two == 37))
    {
        printf("AMEX\n");
    }
    else if (count == 16 && first_two >= 51 && first_two <= 55)
    {
        printf("MASTERCARD\n");
    }
    else if ((count == 13 || count == 16) && first_one == 4)
    {
        printf("VISA\n");
    }
    else
    {
        printf("INVALID\n");
    }
}
