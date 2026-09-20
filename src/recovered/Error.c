extern int near rootWnd;
extern int far pascal MessageBox(int window, char far *text,
                                  char far *caption, unsigned style);

void Error(char far *text)
{
    MessageBox(rootWnd, text, "Error Message", 0x10);
}
