#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int s_strcspn(char *a, char *b)
{ return strcspn(a, b); }

int main()
{
    int i;

    i=s_strcspn("   AAAAAA", "A");
    i=s_strcspn("   1234e5", "eE");

    printf("%d\n", i);

    return 0;


}
