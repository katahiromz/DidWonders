#ifdef __GNUC__
    #pragma ms_struct on
#endif

#include <windows.h>
#include <stdio.h>

#include <pshpack2.h>
typedef struct {
  WINBOOL fShowAllObjects : 1;
  WINBOOL fShowExtensions : 1;
  WINBOOL fNoConfirmRecycle : 1;
  WINBOOL fShowSysFiles : 1;
  WINBOOL fShowCompColor : 1;
  WINBOOL fDoubleClickInWebView : 1;
  WINBOOL fDesktopHTML : 1;
  WINBOOL fWin95Classic : 1;
  WINBOOL fDontPrettyPath : 1;
  WINBOOL fShowAttribCol : 1;
  WINBOOL fMapNetDrvBtn : 1;
  WINBOOL fShowInfoTip : 1;
  WINBOOL fHideIcons : 1;
  WINBOOL fWebView : 1;
  WINBOOL fFilter : 1;
  WINBOOL fShowSuperHidden : 1;
  WINBOOL fNoNetCrawling : 1;
  DWORD dwWin95Unused;
  UINT uWin95Unused;
  LONG lParamSort;
  int iSortDirection;
  UINT version;
  UINT uNotUsed;
  WINBOOL fSepProcess: 1;
  WINBOOL fStartPanelOn: 1;
  WINBOOL fShowStartPage: 1;
  WINBOOL fAutoCheckSelect: 1;
  WINBOOL fIconsOnly: 1;
  WINBOOL fShowTypeOverlay: 1;
  WINBOOL fShowStatusBar : 1;
  UINT fSpareFlags : 9;
} SHELLSTATEA,*LPSHELLSTATEA;
#include <poppack.h>

/*
SHELLSTATEA size: 32
SHELLSTATEA align: 2

00000000 WINBOOL fShowAllObjects : 1;
00000000
00000000
00000000
11111111 DWORD dwWin95Unused;
11111111
11111111
11111111
00000000 UINT uWin95Unused;
00000000
00000000
00000000
11111111 LONG lParamSort;
11111111
11111111
11111111
00000000 int iSortDirection;
00000000
00000000
00000000
00000000 UINT version;
00000000
00000000
00000000
11111111 UINT uNotUsed;
11111111
11111111
11111111
00000001 WINBOOL fSepProcess: 1; ... UINT fSpareFlags : 9;
11111111
00000000 (padding)
00000000
*/

int main(void) {
    SHELLSTATEA ss;
    LPBYTE pb;
    int i, j;

    printf("SHELLSTATEA size: %d\n", (int)sizeof(SHELLSTATEA ));
    printf("SHELLSTATEA align: %d\n", (int)__alignof(SHELLSTATEA ));

    ZeroMemory(&ss, sizeof(ss));
    ss.dwWin95Unused = 0xFFFFFFFF;
    ss.lParamSort = 0xFFFFFFFF;
    ss.uNotUsed = 0xFFFFFFFF;
    ss.fSpareFlags = 0x1FF;

    pb = (LPBYTE)&ss;
    for (i = 0; i < sizeof(ss); ++i) {
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
