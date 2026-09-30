/* Round 6: keep_original_source_live */
/* Round 5: literal_parent_strlib */
/* Round 1, variant 2: strlib hypothesis. */
/* Test whether the target's two inline copy sequences arise from simple
 * far-string copy loops under C7 optimization rather than library calls. */
extern char far Dx8[];
extern char near curFontPtr[];
extern char far *far strcpy(char far *destination, char far *source);
extern char far *strcat(char far *dest, const char far *src);


extern void far *_fmemcpy(void far *destination, const void far *source, unsigned int count);
extern char far *strchr(char far *text, int ch);
extern char far *strstr(char far *text, char far *needle);
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
  char buffer[256];
  int count;
  int i;
  int end;
  unsigned int perm_fileType_2;
  perm_fileType_2 = fileType;
  SendDlgItemMessage(dialog, 0x194, 0x000b, 0, 0L);
  strcpy(buffer, Dx8 + 0x94a0);
  if (perm_fileType_2 != 0xc010)
  {
    strcat(buffer, Dx8 + 0x9f10);
  }
  DlgDirList(dialog, buffer, 0x194, 0x193, perm_fileType_2);
  if (strchr(Dx8 + 0x94a0, ':') == 0)
    DlgDirList(dialog, Dx8 + 0x9f10, 0x194, 0x193, perm_fileType_2);
  SendDlgItemMessage(dialog, 0x194, 0x040a, 0, (unsigned long) buffer);
  count = (int) SendDlgItemMessage(dialog, 0x194, 0x040c, 0, 0L);
  if (count > 0 && buffer[0] != '[')
  {
    SendDlgItemMessage(dialog, 0x194, 0x000b, 0, 0L);
    for (;;)
    {
      SendDlgItemMessage(dialog, 0x194, 0x040a, count - 1, (unsigned long) buffer);
      if (buffer[0] == '[')
      {
        SendDlgItemMessage(dialog, 0x194, 0x0403, count - 1, 0L);
        SendDlgItemMessage(dialog, 0x194, 0x0402, 0, (unsigned long) buffer);
      }
      if (buffer[0] != '[')
        break;
    }

  }
  SendDlgItemMessage(dialog, 0x194, 0x000b, 1, 0L);
  InvalidateRect(GetDlgItem(dialog, 0x194), 0, 1);
  if (strstr(Dx8 + 0x94a0, curFontPtr + 70) != 0)
    *(Dx8 + 0x94a0) = 0;
  SetDlgItemText(dialog, 0x191, Dx8 + 0x9f10);
}





