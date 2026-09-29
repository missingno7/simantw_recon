/* Round 6: keep_original_source_live */
/* Round 5: literal_parent_strlib */
/* Round 1, variant 2: strlib hypothesis. */
/* Test whether the target's two inline copy sequences arise from simple
 * far-string copy loops under C7 optimization rather than library calls. */
extern char far Dx8[];
extern char __based(__segname("DGROUP")) curFontPtr[];
extern char far *far strcpy(char far *destination, char far *source);
extern char far *strcat(char far *dest, const char far *src);


extern void far *_fmemcpy(void far *destination, const void far *source, unsigned int count);
extern char far *strchr(char far *text, int ch);
extern char far *strstr(char far *text, char near *needle);
extern int far pascal DlgDirList(int dialog, char far *pathSpec, int listId,
                                 int staticId, unsigned int fileType);
extern long far pascal SendDlgItemMessage(int dialog, int item, unsigned int message,
                                         unsigned int wParam, unsigned long lParam);
extern int far pascal GetDlgItem(int dialog, int item);
extern void far pascal InvalidateRect(int window, void far *rect,
                                      unsigned flags);

extern int far pascal SetDlgItemText(int dialog, int item, char far *text);
struct ListBuffer { char far *source; char buffer[256]; };
void far UpdateListBox(int dialog, unsigned int fileType)
{
  struct ListBuffer work;
  int count;
  int i;
  int end;
  SendDlgItemMessage(dialog, 0x194, 0x000b, 0, 0L);
  work.source = Dx8 + 0x94a0;
  strcpy(work.buffer, work.source);
  if (fileType != 0xc010)
  {
    strcat(work.buffer, Dx8 + 0x9f10);
  }
  DlgDirList(dialog, work.buffer, 0x194, 0x193, fileType);
  if (strchr(work.source, ':') == 0)
    DlgDirList(dialog, Dx8 + 0x9f10, 0x194, 0x193, fileType);
  SendDlgItemMessage(dialog, 0x194, 0x040a, 0, (unsigned long) work.buffer);
  count = (int) SendDlgItemMessage(dialog, 0x194, 0x040c, 0, 0L);
  if (count > 0 && work.buffer[0] != '[')
  {
    SendDlgItemMessage(dialog, 0x194, 0x000b, 0, 0L);
    for (;;)
    {
      SendDlgItemMessage(dialog, 0x194, 0x040a, count - 1, (unsigned long) work.buffer);
      if (work.buffer[0] != '[')
        break;
      SendDlgItemMessage(dialog, 0x194, 0x0403, count - 1, 0L);
      SendDlgItemMessage(dialog, 0x194, 0x0402, 0, (unsigned long) work.buffer);
      if (work.buffer[0] != '[')
        break;
    }

  }
  SendDlgItemMessage(dialog, 0x194, 0x000b, 1, 0L);
  InvalidateRect(GetDlgItem(dialog, 0x194), 0, 1);
  if (strstr(work.source, curFontPtr + 70) != 0)
    *work.source = 0;
  SetDlgItemText(dialog, 0x191, Dx8 + 0x9f10);
}

