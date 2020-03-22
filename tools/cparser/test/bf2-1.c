#ifdef __GNUC__
    #pragma ms_struct reset
#endif

#include <windows.h>
#include <stdio.h>

#include <pshpack1.h>
typedef struct {
  int fShowAllObjects : 1;
  int fShowExtensions : 1;
  int fNoConfirmRecycle : 1;
  int fShowSysFiles : 1;
  int fShowCompColor : 1;
  int fDoubleClickInWebView : 1;
  int fDesktopHTML : 1;
  int fWin95Classic : 1;
  int fDontPrettyPath : 1;
  int fShowAttribCol : 1;
  int fMapNetDrvBtn : 1;
  int fShowInfoTip : 1;
  int fHideIcons : 1;
  int fWebView : 1;
  int fFilter : 1;
  int fShowSuperHidden : 1;
  int fNoNetCrawling : 1;
  unsigned long dwWin95Unused;
  unsigned int uWin95Unused;
  long lParamSort;
  int iSortDirection;
  unsigned int version;
  unsigned int uNotUsed;
  int fSepProcess: 1;
  int fStartPanelOn: 1;
  int fShowStartPage: 1;
  int fAutoCheckSelect: 1;
  int fIconsOnly: 1;
  int fShowTypeOverlay: 1;
  int fShowStatusBar : 1;
  unsigned int fSpareFlags : 9;
} SHELLSTATEA,*LPSHELLSTATEA;
#include <poppack.h>

/*
SHELLSTATEA size: 32
SHELLSTATEA align: 1

00000000 WINBOOL fShowAllObjects : 1; ...
00000000
00000000 int fNoNetCrawling : 1;
00000000
11111111 unsigned long dwWin95Unused;
11111111
11111111
11111111
00000000 unsigned int uWin95Unused;
00000000
00000000
00000000
11111111 long lParamSort;
11111111
11111111
11111111
00000000 int iSortDirection;
00000000
00000000
00000000
00000000 unsigned int version;
00000000
00000000
00000000
11111111 unsigned int uNotUsed;
11111111
11111111
11111111
00000001 int fSepProcess: 1; ... unsigned int fSpareFlags : 9;
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
