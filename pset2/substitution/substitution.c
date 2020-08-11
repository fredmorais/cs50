#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

bool keyHasLetter(char a, int x, char array[]);
int alphabetIndex(char a);

int main(int argc, string argv[])
{
    //If program executed with no or more than 1 arguments the program should print an error and return from main a value of 1
    if (argc != 2)
    {
        printf("Error: incorrect number of arguments!\n");
        return 1;
    }

    //If key does not have exactly 26 characters the program should print an error and return from main a value of 1
    if (strlen(argv[1]) != 26)
    {
        printf("Error: key does not have 26 characters\n");
        return 1;
    }

    //If key has non-alphabetical character then print error and return from main a value of 1
    for (int i = 0; i < strlen(argv[1]); i++)
    {
        if (!(argv[1][i] >= 'a' && argv[1][i] <= 'z') && !(argv[1][i] >= 'A' && argv[1][i] <= 'Z'))
        {
            printf("Error: key contains non-alphabetical characters\n");
            return 1;
        }
    }

    //Transform key to lower-case
    char key[26];
    for (int i = 0; i < 26; i++)
    {
        if (argv[1][i] >= 'A' && argv[1][i] <= 'Z')
        {
            key[i] = tolower(argv[1][i]);
        }
        else
        {
            key[i] = argv[1][i];
        }
    }

    //If key does not have each letter once then print error and return from main a value of 1
    for (int i = 0; i < 26; i++)
    {
        if (keyHasLetter(key[i], i, key))
        {
            printf("Error: key contains repeated letters\n");
            return 1;
        }
    }

    //Output plaintext: and get the string from user
    string plaintext = get_string("plaintext: ");

    //Output ciphertext: followed by the plaintext's corresponding ciphertext
    printf("ciphertext: ");
    for (int i = 0; i < strlen(plaintext); i++)
    {
        //Do not affect non-alphabetical characters
        if ((plaintext[i] >= 'a' && plaintext[i] <= 'z') || (plaintext[i] >= 'A' && plaintext[i] <= 'Z'))
        {
            //Preserve case
            if (plaintext[i] >= 'A' && plaintext[i] <= 'Z')
            {
                int index = alphabetIndex(tolower(plaintext[i]));
                printf("%c", toupper(key[index]));
            }
            else
            {
                int index = alphabetIndex(plaintext[i]);
                printf("%c", key[index]);
            }
        }
        else
        {
            printf("%c", plaintext[i]);
        }
    }
    printf("\n");

    //Exit program by returning 0 from main
    return 0;
}

//Checks if the key contains a given letter
bool keyHasLetter(char a, int x, char array[])
{
    for (int i = 0; i < 26; i++)
    {
        if (array[i] == a && x != i)
        {
            return true;
        }
    }
    return false;
}

//Returns the index of a letter in the alphabet
int alphabetIndex(char a)
{
    char alphabet[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
    for (int i = 0; i < 26; i++)
    {
        if (alphabet[i] == a)
        {
            return i;
        }
    }
    return 999;
}