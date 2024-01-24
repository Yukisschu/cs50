#include <cs50.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int get_word(string text);
int get_letter(string text);
int get_sentence(string text);

int main(void)
{
    int w, l, s;
    float i, L, S;
    string x = get_string("Text: ");
    w = get_word(x);
    l = get_letter(x);
    s = get_sentence(x);
    // L = 100 * l / w;
    // S = 100 * s / w;
    L = (float) l / w * 100.0;
    S = (float) s / w * 100.0;
    i = (0.0588 * L) - (0.296 * S) - 15.8;
    // printf("%i %i %i %i %i %f", w, l, s, L, S, i);
    // L = 100 * l / w and L = l / w * 100 yield different results as it will get int every step
    if (i < 1)
    {
        printf("Before Grade 1");
    }
    else if (i >= 1 && i <= 16)
    {
        int j = round(i);
        printf("Grade %i", j);
    }
    else
    {
        printf("Grade 16+");
    }
    printf("\n");
}

int get_word(string text)
{
    int count = 1;
    for (int index = 0; text[index] != '\0'; index++)
    {
        if (text[index] == ' ')
        {
            count++;
        }
    }
    return count;
}

int get_letter(string text)
{
    int count = 0;
    for (int index = 0; text[index] != '\0'; index++)
    {
        if ((text[index] >= 'a' && text[index] <= 'z') || (text[index] >= 'A' && text[index] <= 'Z'))
        {
            count++;
        }
    }
    return count;
}

int get_sentence(string text)
{
    int count = 0;
    for (int index = 0; text[index] != '\0'; index++)
    {
        if (text[index] == '.' || text[index] == '!' || text[index] == '?')
        {
            count++;
        }
    }
    return count;
}