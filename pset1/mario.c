#include <stdio.h>
#include <cs50.h>

int main(void)
{
    int size = get_int("How tall should the pyramid be?\n");

    while (size == 0 || size == -1 || size == 9)
    {
        size = get_int("How tall should the pyramid be?\n");
    }


    if (size > 0 && size < 9)
    {
        for (int i = 0; i < size; i++)
        {
            for (int z = size - i; z > 1; z--)
            {
                printf(" ");
            };
            for (int z = 0; z <= i; z++)
            {
                printf("#");
            };
            printf("  ");
            for (int z = 0; z <= i; z++)
            {
                printf("#");
            };
            printf("\n");
        };
    };
}
