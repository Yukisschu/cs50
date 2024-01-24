#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void subs(string key, string input);

int main(int argc, string argv[])
{
    if (argc != 2)
    { // just argc
        printf("Usage: ./substitution key");
        return 1;
    }
    if (strlen(argv[1]) != 26)
    { // argv[1]
        printf("Key must contain 26 characters.");
        return 1;
    }
    for (int i = 0; i < 26; i++)
    {
        if (argv[1][i] < 'A' || (argv[1][i] > 'Z' && argv[1][i] < 'a') || argv[1][i] > 'z')
        {
            printf("Key must contain 26 characters.");
            return 1;
        }
    }
    string keyu = malloc(27 * sizeof(char));
    // int distance [26];
    // int sum = 0;
    for (int j = 0; j < 26; j++)
    { // need to use different character for variable name, cannot use i again
        keyu[j] = toupper(argv[1][j]);
        // distance[j] = keyu[j] - 'A';
        // sum += distance;
    }
    keyu[26] = '\0';

    // for (int m = 0; m < 26; m++){
    //     for (int n = m + 1; n < 26; n++ ){
    //         if (distance[m] == distance[n]){
    //             printf("Key must contain 26 characters.");
    //             return 1;
    //         }
    //     }
    // }

    for (int m = 0; m < 26; m++)
    {
        for (int n = m + 1; n < 26; n++)
        {
            if (keyu[m] == keyu[n])
            {
                printf("Key must contain 26 characters.");
                return 1;
            }
        }
    }

    // if (sum != 325){ //can be multiple dupicates that still have the sum of 325
    //     printf("Key must contain 26 characters.");
    //     return 1;
    // }

    string plaintext = get_string("plaintext:  ");
    // printf("\n");
    subs(keyu, plaintext); // do not need asignment for void function
    printf("ciphertext: %s", plaintext);
    printf("\n");
    return 0;
}

// void subs(string key, string input)
// {
//     string keyl = (char *)malloc(27 * sizeof(char));

//     for (int i = 0; i < 26; i++){
//         keyl[i] = tolower(key[i]);
//     }
//     keyl[26] = '\0';

//     for (int i = 0, int n = strlen(input); i < n; i++){
//         if (input[i] > 'A' && input[i] < 'Z'){
//             input[i] = key[i];
//         }
//         if (input[i] > 'a' && input[i] < 'z'){
//             input[i] = keyl[i];
//         }
//     }
//     free(keyl);
// }

void subs(char *key, char *input)
{
    char *keyl = (char *) malloc(27 * sizeof(char));

    for (int i = 0; i < 26; i++)
    {
        keyl[i] = tolower(key[i]);
    }
    keyl[26] = '\0';

    int n = strlen(input);

    for (int i = 0; i < n; i++)
    {
        if (input[i] >= 'A' && input[i] <= 'Z')
        {
            input[i] = key[(input[i] - 'A')]; // need to calculate which character it is
        }
        if (input[i] >= 'a' && input[i] <= 'z')
        {
            input[i] = keyl[(input[i] - 'a')];
        }
    }

    free(keyl); // remember to free the dynamically allocated memory
}