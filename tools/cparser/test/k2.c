#ifdef __GNUC__
    #pragma ms_struct on
#endif

#include <windows.h>
#include <stdio.h>

#include <pshpack1.h>
typedef struct X1 {
    short a : 1;
    char b;
} X1;
#include <poppack.h>

#include <pshpack2.h>
typedef struct X2 {
    short a : 1;
    char b;
} X2;
#include <poppack.h>

#include <pshpack4.h>
typedef struct X4 {
    short a : 1;
    char b;
} X4;
#include <poppack.h>

#include <pshpack8.h>
typedef struct X8 {
    short a : 1;
    char b;
} X8;
#include <poppack.h>

/*
    short a : 1;
    char b;
        size    pack    align   b
    X1  3       1       1       2
    X2  4       2       2       2
    X4  4       4       2       2
    X8  4       8       2       2
*/

int main(void) {
    printf("X1 size: %d\n", (int)sizeof(X1));
    printf("X1 align: %d\n", (int)__alignof(X1));
    printf("X1 b: %d\n", (int)FIELD_OFFSET(X1, b));

    printf("X2 size: %d\n", (int)sizeof(X2));
    printf("X2 align: %d\n", (int)__alignof(X2));
    printf("X2 b: %d\n", (int)FIELD_OFFSET(X2, b));

    printf("X4 size: %d\n", (int)sizeof(X4));
    printf("X4 align: %d\n", (int)__alignof(X4));
    printf("X4 b: %d\n", (int)FIELD_OFFSET(X4, b));

    printf("X8 size: %d\n", (int)sizeof(X8));
    printf("X8 align: %d\n", (int)__alignof(X8));
    printf("X8 b: %d\n", (int)FIELD_OFFSET(X8, b));

    return 0;
}
