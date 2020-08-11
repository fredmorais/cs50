#include <stdio.h>
#include <cs50.h>

int main(void)
{
    string name = get_string("Hello, there! What is your name?\n");

    printf("Hello, %s!\n", name);
}