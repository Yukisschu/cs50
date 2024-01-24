#include <cs50.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int only_digit(string input);
int get_num(string input);

int main(int argc, string argv[]) // the input from cl argument is string
{
    if (argc != 2 || only_digit(argv[1]) != 0)
    {
        // printf("%d",argc);
        printf("Usage: ./caesar key");
        return 1;
    }
    int key = get_num(argv[1]);
    // printf("%d\n",key);
    char *input = get_string("plaintext:  ");
    int length = strlen(input);
    for (int i = 0; i < length; i++)
    {
        if (input[i] >= 'a' && input[i] <= 'z')
        {
            input[i] = 'a' + ((input[i] - 'a' + key) % 26);
        }
        else if (input[i] >= 'A' && input[i] <= 'Z')
        {
            input[i] = 'A' + ((input[i] - 'A' + key) % 26);
        }
    }
    printf("ciphertext: %s", input);
    printf("\n");
    return 0;
}

int only_digit(string input)
{
    int length = strlen(input);
    for (int i = 0; i < length; i++)
    {
        if (input[i] < '0' || input[i] > '9')
        {
            return 1;
        }
    }
    return 0;
}

int get_num(string input)
{
    int length = strlen(input);
    int num = 0;
    for (int i = 0; i < length; i++)
    {
        num += (input[i] - '0') * pow(10, (length - 1 - i));
    }
    return num;
}