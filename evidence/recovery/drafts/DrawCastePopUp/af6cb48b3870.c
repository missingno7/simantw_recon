/* Measure digit width, position the popup from its window rectangle, then draw blue/red population rows and wait for the held-button close. */
struct WinRect {
    int left;
    int top;
    int right;
    int bottom;
};

union WinRectAddress {
    struct {
        unsigned int offset;
        unsigned int segment;
    } words;
    struct WinRect far *rect;
};

extern int far GamePaused;
extern int far LessonTemp;
extern int near rootWnd;
extern int near _foreColor;
extern int near win_hwnd[];
extern unsigned int near win_handles[];
extern int near CastePopB[];
extern int near CastePopR[];

extern void far SetPause(int pause);
extern int far pascal GetClientRect(int window, struct WinRect far *rect);
extern int far pascal GetSystemMetrics(int index);
extern void far win_GetObjRect(int object, struct WinRect far *rect);
extern void far win_LockWin(int window);
extern void far win_UnlockWin(int window);
extern int far win_Open(int window, ...);
extern int far MySetCapture(int window);
extern void far MyReleaseCapture(void);
extern void far ButtonHeldInit(void);
extern int far ButtonHeld(void);
extern int far win_Events(void);
extern int far win_IsWinOpen(int window);
extern void far win_Close(int window);
extern void far font_SetFont(int font);
extern int far font_CharWidth(int character);
extern int far font_FontHeight(void);
extern void far MSClipStart(int window);
extern void far MSClipEnd(void);
extern void far win_SetColorFromObjNum(int objectNumber);
extern int far sprintf(char far *buffer, char far *format, ...);
extern void far font_PrintStr(int x, int y, char far *text);
extern void far GBoxFill(int left, int top, int right, int bottom, int color);

void far DrawCastePopUp(void)
{
  struct WinRect clientRect;
  struct WinRect objectRect;
  struct WinRect popupRect;
  volatile union WinRectAddress windowAddress;
  int savedPause;
  int i;
  int character;
  int digitWidth;
  int fontHeight;
  int barX;
  int y;
  int maxPop;
  int blueWidth;
  int redWidth;
  int availableWidth;
  int rowStep;
  int extraHeight;
  int extraRemainder;
  int population;
  char text[30];
  savedPause = GamePaused;
  SetPause(1);
  LessonTemp = 1;
  windowAddress.words.segment = 2;
  if (win_handles[68] | win_handles[69])
  {
    GetClientRect(rootWnd, &clientRect);
    win_GetObjRect(0x2201, &objectRect);
    win_LockWin(0x1700);
    windowAddress.words.offset = win_handles[46];
    windowAddress.words.segment = win_handles[47];
    y = windowAddress.rect->left - windowAddress.rect->right;
    y -= 2 * GetSystemMetrics(7);
    if (objectRect.right > clientRect.right)
      y += clientRect.right;
    win_Open(0x1700, y, 0);
    win_UnlockWin(0x1700);
  }
  else
  {
    win_Open(0x1700);
  }
  MySetCapture(win_hwnd[23]);
  ButtonHeldInit();
  win_GetObjRect(0x1702, &popupRect);
  font_SetFont(2);
  digitWidth = 0;
  for (character = '0'; character <= '9'; ++character)
  {
    i = font_CharWidth(character);
    if (i > digitWidth)
      digitWidth = i;
  }

  barX = popupRect.left + 2 + digitWidth * 4;
  availableWidth = popupRect.right - barX;
  fontHeight = font_FontHeight();
  extraHeight = popupRect.bottom - 12 * fontHeight - popupRect.top + 3;
  extraRemainder = extraHeight % 5;
  rowStep = extraHeight / 5;
  maxPop = 1;
  for (i = 1; i < 6; ++i)
  {
    if (CastePopB[i] > maxPop)
      maxPop = CastePopB[i];
    if (CastePopR[i] > maxPop)
      maxPop = CastePopR[i];
  }

  MSClipStart(win_hwnd[23]);
  y = popupRect.top;
  extraHeight = 0;
  i = 0;
  if (i < 6)
    do
  {
    extraHeight += extraRemainder;
    if (extraHeight > 5)
    {
      ++y;
      extraHeight -= 5;
    }
    if (i == 5)
      --y;
    population = CastePopB[i];
    blueWidth = (int) (((long) population) * availableWidth / maxPop);
    population = CastePopR[i];
    redWidth = (int) (((long) population) * availableWidth / maxPop);
    win_SetColorFromObjNum(0x1703);
    sprintf(text, "%d", CastePopB[i]);
    font_PrintStr(popupRect.left, y, text);
    if (i != 0 && blueWidth != 0)
      GBoxFill(barX, y + 1, barX + blueWidth, y + fontHeight - 3, _foreColor);
    win_SetColorFromObjNum(0x1704);
    sprintf(text, "%d", CastePopR[i]);
    font_PrintStr(popupRect.left, y + fontHeight, text);
    if (i != 0 && redWidth != 0)
      GBoxFill(barX, y + fontHeight + 1, barX + redWidth, y + 2 * fontHeight - 3, _foreColor);
    y += 2 * fontHeight + rowStep;
    ++i;
  }
  while (i < 6);
  MSClipEnd();
  font_SetFont(0);
  ButtonHeldInit();
  do
  {
    win_Events();
  }
  while (win_IsWinOpen(0x1700) && ButtonHeld());
  MyReleaseCapture();
  win_Close(0x1700);
  SetPause(savedPause);
}

