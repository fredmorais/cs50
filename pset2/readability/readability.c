#include <stdio.h>
#include <cs50.h>

int main(void)
{
    //Get string from user
    string text = get_string("Input: ");

    int letters = 0;
    int words = 0;
    int sentences = 0;

    for (int i = 0; text[i] != '\0'; i++)
    {
        //Count number of letters
        if ((text[i] >= 'a' && text[i] <= 'z') || (text[i] >= 'A' && text[i] <= 'Z'))
        {
            letters++;
        }
        //Count number of words
        else if (text[i] == ' ')
        {
            words++;
        }
        //Count number of sentences
        else if (text[i] == '.' || text[i] == '?' || text[i] == '!')
        {
            sentences++;
        }
    }
    //Add word because last word does not have a space after it
    words++;

    float index;
    float L;
    float S;

    L = (float) letters / (float) words * 100;
    S = (float) sentences / (float) words * 100;

    //Calculate GRADE X using the Coleman-Liau formula
    index = 0.0588 * L - 0.296 * S - 15.8;

    //Output result
    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index > 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %.0f\n", index);
    }
}