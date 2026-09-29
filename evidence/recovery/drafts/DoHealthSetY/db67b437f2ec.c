struct WinRect {
    int left;
    int top;
    int right;
    int bottom;
};
/* Use separate offset and selector values while retaining the far ABI. */
struct HealthRect { int left, top, right, bottom; };
struct EditEvent { char reserved[8]; int x; int y; };
extern void far win_GetObjRect(int object, struct WinRect far *rect);

extern int far MeWarnHealth;
void far DoHealthSetY(struct EditEvent far *event, int objectNumber)
{
  register int savedNumber = objectNumber;
  struct HealthRect rect;
  __segment eventSelector = (__segment)event;
  unsigned int eventOffset = (unsigned int)event;
  struct EditEvent __based(eventSelector) *eventView = (struct EditEvent *)eventOffset;
  int numerator;
  int denominator;
  win_GetObjRect(savedNumber, &rect);
  if (savedNumber == 0x11)
  {
    denominator = rect.bottom - rect.top;
    numerator = (rect.bottom - eventView->y) * 100;
  }
  else
  {
    numerator = (eventView->x - rect.left) * 100;
    denominator = rect.right - rect.left;
  }
  MeWarnHealth = numerator / denominator;
}
