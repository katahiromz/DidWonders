#ifdef __GNUC__
    #pragma ms_struct on
#endif

#include <windows.h>
#include <stdio.h>

#include <pshpack1.h>
  typedef struct {
    unsigned short cLength;
    unsigned short nVersion;
        int fFullPathTitle : 1;
        int fSaveLocalView : 1;
        int fNotShell : 1;
        int fSimpleDefault : 1;
        int fDontShowDescBar : 1;
        int fNewWindowMode : 1;
        int fShowCompColor : 1;
        int fDontPrettyNames : 1;
        int fAdminsCreateCommonGroups : 1;
        unsigned int fUnusedFlags : 7;
    unsigned int fMenuEnumFilter;
  } CABINETSTATE,*LPCABINETSTATE;
#include <poppack.h>

/*
CABINETSTATE size: 12
CABINETSTATE align: 1

00000000 WORD cLength;
00000000
11111111 WORD nVersion;
11111111
00000000 WINBOOL fFullPathTitle : 1; ...
01111111 WINBOOL fAdminsCreateCommonGroups : 1; UINT fUnusedFlags: 7;
00000000 (padding)
00000000
11111111 UINT fMenuEnumFilter;
11111111
11111111
11111111
*/

int main(void) {
    CABINETSTATE cs;
    LPBYTE pb;
    int i, j;

    printf("CABINETSTATE size: %d\n", (int)sizeof(CABINETSTATE));
    printf("CABINETSTATE align: %d\n", (int)__alignof(CABINETSTATE));

    ZeroMemory(&cs, sizeof(cs));
    cs.nVersion = 0xFFFF;
    cs.fUnusedFlags = 0x7F;
    cs.fMenuEnumFilter = 0xFFFFFFFF;

    pb = (LPBYTE)&cs;
    for (i = 0; i < sizeof(cs); ++i) {
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
