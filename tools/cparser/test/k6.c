#ifdef __GNUC__
    #pragma ms_struct on
#endif

#include <windows.h>
#include <stdio.h>

#include <pshpack1.h>
typedef struct X1 {
    short a : 7;
} X1;
#include <poppack.h>

#include <pshpack2.h>
typedef struct X2 {
    short a : 7;
} X2;
#include <poppack.h>

#include <pshpack4.h>
typedef struct X4 {
    short a : 7;
} X4;
#include <poppack.h>

#include <pshpack8.h>
typedef struct X8 {
    short a : 7;
} X8;
#include <poppack.h>

/*
    short a : 7;
        size    pack    align
    X1  2       1       1
    X2  2       2       2
    X4  2       4       2
    X8  2       8       2
*/

int main(void) {
    printf("X1 size: %d\n", (int)sizeof(X1));
    printf("X1 align: %d\n", (int)__alignof(X1));

    printf("X2 size: %d\n", (int)sizeof(X2));
    printf("X2 align: %d\n", (int)__alignof(X2));

    printf("X4 size: %d\n", (int)sizeof(X4));
    printf("X4 align: %d\n", (int)__alignof(X4));

    printf("X8 size: %d\n", (int)sizeof(X8));
    printf("X8 align: %d\n", (int)__alignof(X8));

    return 0;
}
