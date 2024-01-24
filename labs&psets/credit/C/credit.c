#include <cs50.h>
#include <stdio.h>
#include <math.h>
#include <stdint.h>

int get_digit(long long num, int digit);
int get_length(long long num);

int main(void)
{
    long long num;
    int a, b, j, length;
    int k = 0;
    num = get_long_long("card number: ");
    // float l = log10 (num);
    // int length = (int)l + 1;
    length = get_length(num);
    a = get_digit(num, length);
    b = get_digit(num, length - 1);
    // printf("%d\n", length);
    for (int i = 1; i <= 16; i++)
    {
        j = get_digit(num, i);
        if (i % 2 == 0)
        {
            j = j * 2;
        }
        if (j >= 10)
        {
            j = j/10 + j%10;
        }
        // printf("%d %d \n", j, k);
        k = k + j;
        // printf("%d %d \n", j, k);
        }
    if (a == 4 && k % 10 == 0 && (length == 13 || length == 16))
    {
        printf("VISA\n");
    }
    else if (a == 5 && (b == 1 || b == 2 || b == 3 || b == 4 || b == 5) && k % 10 == 0 && length == 16)
    {
        printf("MASTERCARD\n");
    }
    else if (a == 3 && (b == 4 || b == 7) && k % 10 == 0 && length == 15)
    {
        printf("AMEX\n");
    }
    else
    {
        printf("INVALID\n");
    }
}

int get_digit(long long num, int digit)
{
    int a;
    long long b;
    b = pow(10, (digit - 1));
    a = (num / b) % 10;
    return a;
}

int get_length(long long num)
{
    int a = 0;
    while (num > 0)
    {
    num = num / 10;
    a += 1;
    }
    return a;
}