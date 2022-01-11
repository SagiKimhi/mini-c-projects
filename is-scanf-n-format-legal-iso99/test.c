#include <stdio.h>
#include <stdlib.h>

#define MAX_LINE_LEN 101

int main(int argc, char **argv)
{
    char in[MAX_LINE_LEN]={0};
    int inSize=0;
    printf("Enter a string to test how scanf measures the length of its input:\n");
    scanf("%100[^\n,]%n", in, &inSize);
    if (feof(stdin))
        putchar('\n');
    printf("input was: %s\ninput size was: %d\n", in, inSize);

    return 0;
}
