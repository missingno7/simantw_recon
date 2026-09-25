/* Startup and button defaults, followed by the NetBIOS buffer handle and null pointer. */
int near bHelp = {0};
int near mapUserButton[8] = { 15, 0, 1, 3, 7, 6, 5, 10 };
int near yardUserButton[8] = { 15, 0, 1, 3, 7, 6, 5, 10 };
int near paletteFlag = {0};
int near activeAppFlag = 1;
int near captureWnd = {0};
int near fileWaitFlag = {0};
int near theNetBiosBufferH = {0};
char far * near theNetBiosBuffer = {0};
