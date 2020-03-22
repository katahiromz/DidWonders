#include <stdio.h>

int main(void) {
#ifdef _MSC_VER
    printf("%d\n", _MSC_VER);
#endif
#ifdef _MSC_FULL_VER
    printf("%d\n", _MSC_FULL_VER);
#endif
    return 0;
}
