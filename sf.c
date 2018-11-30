#include <stdlib.h>
#include <stdio.h>
#include <string.h>

extern void _start1(void);

int s_strcspn(char *a, char *b)
{ return strcspn(a, b); }

int main()
{
    int i;
    char *c="   1234e5";
    char c1[256];

    // i=s_strcspn("   AAAAAA", "A");
    i=s_strcspn(c, "eE");

    // printf("%d %c\n", i, c[i]);

    strncpy(c1, c, i-1);
    printf("%d %s\n", i, c1);

    _start1();

    return 0;


}
