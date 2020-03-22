#ifdef __GNUC__
    #pragma ms_struct on
#endif

#include <windows.h>
#include <stdio.h>

#include <pshpack1.h>
typedef struct X1 {
    char a : 1;
    short b;
} X1;
#include <poppack.h>

#include <pshpack2.h>
typedef struct X2 {
    char a : 1;
    short b;
} X2;
#include <poppack.h>

#include <pshpack4.h>
typedef struct X4 {
    char a : 1;
    short b;
} X4;
#include <poppack.h>

#include <pshpack8.h>
typedef struct X8 {
    char a : 1;
    short b;
} X8;
#include <poppack.h>

/*
    char a : 1;
    short b;
        size    pack    align   b
    X1  3       1       1       1
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
