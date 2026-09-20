extern int near rootWnd;
extern int far pascal MessageBox(int window, char far *text,
                                  char far *caption, unsigned style);

void PopMsg(char far *text)
{
    MessageBox(rootWnd, text, "Message", 0x40);
}
