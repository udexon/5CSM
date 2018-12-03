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

int print_msg() {
    printf("\n\n20181201 end jonesforth. Back to C.\n"); 
    return 0;
}

int ex_forth(char *FDSEG) {
    _start1(FDSEG); // call jonesforth in subfunction, preserve main stack?
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
 
    mod_array1(); printf("\n");

    // _start1(FDSEG); // call jonesforth in subfunction, preserve main stack?
    ex_forth(FDSEG);

    // mod_array1();     mod_array1();  // sl.c: 2 x mod_array1()?
    // this code produced no error. still same seg fault after next printf()

    print_msg(); // can call other functions in sub function. main stack corrupted?

    printf("\n20181201 end jonesforth. Back to C.\n"); 
    // 2018 1203 0740 still died here despite another mod_array1() next.

    mod_array1(); // sk: another mod_array1() for test.

    return 0;


}
