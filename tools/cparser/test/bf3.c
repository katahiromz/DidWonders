#ifdef __GNUC__
    #pragma ms_struct on
#endif

#include <stdlib.h>
#include <stdio.h>
#include <memory.h>

#include <pshpack1.h>
typedef struct {
    //int a : 8;
    int a : 9;
    int b;
} X,*LPX;
#include <poppack.h>

/*
    size: 8
    int a : 8;
    int b;
11111111
00000000
00000000
00000000
11111111
11111111
11111111
11111111
*/

int main(void) {
    X x;
    unsigned char *pb;
    int i, j;

    printf("X size: %d\n", (int)sizeof(X));
    printf("X align: %d\n", (int)__alignof(X));

    memset(&x, 0, sizeof(x));
    x.a = 0xFF;
    x.b = 0xFFFFFFFF;

    pb = (unsigned char *)&x;
    for (i = 0; i < sizeof(x); ++i) {
        for (j = 0; j < 8; j++) {
            if (*pb & (1 << j))
                putchar('1');
            else
                putchar('0');
        }
        pb++;
    }
    putchar('\n');

    return 0;
}
