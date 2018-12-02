#include <stdlib.h>
#include <stdio.h>
#include <string.h>

extern void _start1(char *);

int s_strcspn(char *a, char *b)
{ return strcspn(a, b); }

int * asm_mod_array(int *ptr,int size);
 
int
mod_array() {
int fren[5]={ 1, 2, 3, 4, 5 };
 
/* call the asm function */
asm_mod_array(fren, 5);

printf("%d %d %d %d %d\n", fren[0], fren[1], fren[2], fren[3], fren[4] );
 
return 0;
}

int
mod_array1() {
int fren[5]={ 1, 2, 3, 4, 5 };
 
/* call the asm function */
// asm_mod_array(fren, 5);

printf("%d %d %d %d %d\n", fren[0], fren[1], fren[2], fren[3], fren[4] );
 
return 0;
}

char *FDSEG; // Forth Data Segment

int main()
{
    int i;
    char *c="   1234e5";
    char c1[256];

    FDSEG=(char *) malloc(65536);

    // i=s_strcspn("   AAAAAA", "A");
    i=s_strcspn(c, "eE");

    // printf("%d %c\n", i, c[i]);

    strncpy(c1, c, i-1);
    printf("%d %s\n", i, c1);

    mod_array();
 
    mod_array1();

    _start1(FDSEG);

    mod_array1();

    printf("\n20181201 end jonesforth. Back to C.\n");

    return 0;


}
