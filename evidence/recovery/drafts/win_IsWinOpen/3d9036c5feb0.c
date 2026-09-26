extern int near win_hwnd[]; extern int far pascal IsWindowVisible(int);
int far win_IsWinOpen(int window) { register volatile int copy=window; register int index; int near * volatile slot; index=copy; index>>=8; slot=&win_hwnd[index]; if(*slot==0) goto no; if(IsWindowVisible(*slot)) return 1; no: return 0; }
