#ifdef __GNUC__
    #pragma ms_struct on
#endif

#include <windows.h>
#include <stdio.h>

typedef struct X0 {
    long a;
    short b;
    char c;
} X0;

#include <pshpack1.h>
typedef struct X1 {
    long a;
    short b;
    char c;
} X1;
#include <poppack.h>

#include <pshpack2.h>
typedef struct X2 {
    long a;
    short b;
    char c;
} X2;
#include <poppack.h>

#include <pshpack4.h>
typedef struct X4 {
    long a;
    short b;
    char c;
} X4;
#include <poppack.h>

#include <pshpack8.h>
typedef struct X8 {
    long a;
    short b;
    char c;
} X8;
#include <poppack.h>

/*
    long a;
    short b;
    char c;

    size    align   a   b   c
    8       4       0   4   6
    7       1       0   4   6
    8       2       0   4   6
    8       4       0   4   6
    8       4       0   4   6
*/

int main(void) {
    printf("X0 size: %d\n", (int)sizeof(X0));
    printf("X0 align: %d\n", (int)__alignof(X0));
    printf("X0 a offset: %d\n", (int)FIELD_OFFSET(X0, a));
    printf("X0 b offset: %d\n", (int)FIELD_OFFSET(X0, b));
    printf("X0 c offset: %d\n", (int)FIELD_OFFSET(X0, c));

    printf("X1 size: %d\n", (int)sizeof(X1));
    printf("X1 align: %d\n", (int)__alignof(X1));
    printf("X1 a offset: %d\n", (int)FIELD_OFFSET(X1, a));
    printf("X1 b offset: %d\n", (int)FIELD_OFFSET(X1, b));
    printf("X1 c offset: %d\n", (int)FIELD_OFFSET(X1, c));

    printf("X2 size: %d\n", (int)sizeof(X2));
    printf("X2 align: %d\n", (int)__alignof(X2));
    printf("X2 a offset: %d\n", (int)FIELD_OFFSET(X2, a));
    printf("X2 b offset: %d\n", (int)FIELD_OFFSET(X2, b));
    printf("X2 c offset: %d\n", (int)FIELD_OFFSET(X2, c));

    printf("X4 size: %d\n", (int)sizeof(X4));
    printf("X4 align: %d\n", (int)__alignof(X4));
    printf("X4 a offset: %d\n", (int)FIELD_OFFSET(X4, a));
    printf("X4 b offset: %d\n", (int)FIELD_OFFSET(X4, b));
    printf("X4 c offset: %d\n", (int)FIELD_OFFSET(X4, c));

    printf("X8 size: %d\n", (int)sizeof(X8));
    printf("X8 align: %d\n", (int)__alignof(X8));
    printf("X8 a offset: %d\n", (int)FIELD_OFFSET(X8, a));
    printf("X8 b offset: %d\n", (int)FIELD_OFFSET(X8, b));
    printf("X8 c offset: %d\n", (int)FIELD_OFFSET(X8, c));

    return 0;
}
