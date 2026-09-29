struct ExpMenuPoint { int x, y; };
struct MSG {
    int hwnd;
    unsigned int message;
    unsigned int wParam;
    long lParam;
    unsigned long time;
    int pt_x;
    int pt_y;
};
/*
 * win_GetEvent: pump pending input messages, then (if a mouse-button
 * transition or a key/space/minus keydown was seen) resolve what the
 * cursor is currently over.  A do-while pumps PeekMessage/Translate/
 * DispatchMessage until no more messages are queued or a "stop" event
 * (WM_LBUTTONDOWN, WM_LBUTTONUP, or WM_KEYDOWN with VK_SPACE/'-') has
 * been seen; the function's own return value is that stop flag.  When it
 * fires, *result is filled: the hit window is the current mouse-capture
 * window if any, else the front (topmost visible) window's child, found
 * by walking GetTopWindow/GetWindow(GW_HWNDNEXT) then GetWindow(GW_CHILD)
 * exactly as the admitted win_* helpers walk sibling/child chains.  Its
 * "INDEX" window property (the same SetProp/GetProp tag win_Swap and
 * INDIRECTDLGPROC use) gives the window's own packed object number.  The
 * cursor position is fetched and mapped into the window's client area
 * directly into result->point, then the window's object bucket
 * (win_handles[windowObj>>8], the same far bucket table as the other win_*
 * members) is scanned back-to-front for a visible object (flags bit 1,
 * matching win_SetColorFromObj's flags placement) whose leading rect
 * contains the point; a hit's low byte replaces the window number's low
 * byte, a miss leaves the window number alone, and if that ever comes out
 * zero a distinct negative sentinel (0xff00 | high byte of windowObj) is
 * written instead.
 */
struct CursorRect {
    int left;
    int top;
    int right;
    int bottom;
};

struct CursorPoint {
    int x;
    int y;
};

struct HitObject {
    struct CursorRect rect;
    unsigned char pad[0x24 - 8];
    unsigned char flags;
};

struct WinBucket {
    unsigned char reserved[0xc];
    int objectCount;
    unsigned char gap[0x2c - 0xe];
    struct HitObject far *objects[256];
};

struct Msg {
    unsigned hwnd;
    unsigned message;
    unsigned wParam;
    unsigned long lParam;
    unsigned long time;
    int ptX;
    int ptY;
};

struct DialogEvent {
    unsigned char reserved[8];
    struct CursorPoint point;
    int object;
};

extern struct WinBucket far * near win_handles[];
extern int near rootWnd;

extern int far pascal PeekMessage(struct MSG far *message,
                                  int hwnd, unsigned int first,
                                  unsigned int last, unsigned int remove);

extern int far pascal TranslateMessage(struct MSG far *message);

extern long far pascal DispatchMessage(struct MSG far *message);

extern int MyGetCapture(void);

extern int far pascal GetTopWindow(int window);

extern int far pascal IsWindowVisible(int window);

extern int far pascal GetWindow(int window, int command);

extern unsigned int far pascal GetProp(int window, char far *name);

extern int far pascal GetCursorPos(void far *point);

extern int far pascal ScreenToClient(int window, struct ExpMenuPoint far *point);

extern int far PointInRect(struct CursorPoint far *point, struct CursorRect far *rect);

#define WM_KEYDOWN      0x100
#define WM_LBUTTONDOWN  0x201
#define WM_LBUTTONUP    0x202
#define VK_SPACE        0x20
#define GW_HWNDNEXT     2
#define GW_CHILD        4

int far win_GetEvent(struct DialogEvent far *result)
{
  struct Msg msg;
  int stop;
  unsigned w;
  int windowObj;
  struct WinBucket far *bucket;
  struct HitObject far *object;
  int index;
  stop = 0;
  if (!stop && PeekMessage(&msg, 0, 0, 0, 1))
  {
    do
    {
      if (stop)
        break;
      if (msg.message == WM_LBUTTONDOWN || msg.message == WM_LBUTTONUP)
        stop = 1;
      if (msg.message == WM_KEYDOWN && (msg.wParam == VK_SPACE || msg.wParam == '-'))
        stop = 1;
      TranslateMessage(&msg);
      DispatchMessage(&msg);
    }
    while (PeekMessage(&msg, 0, 0, 0, 1));
  }
  if (!stop)
    return stop;
  w = MyGetCapture();
  result->object = 0;
  if (w == 0)
  {
    w = GetTopWindow(rootWnd);
    if (w != 0)
    {
      do
      {
        if (IsWindowVisible(w))
          break;
        w = GetWindow(w, GW_HWNDNEXT);
      }
      while (w != 0);
      if (w != 0)
      {
        if (GetWindow(w, GW_CHILD) != 0)
          w = GetWindow(w, GW_CHILD);
      }
    }
  }
  if (w != 0)
  {
    windowObj = GetProp(w, "INDEX");
    if (windowObj > 0)
    {
      GetCursorPos(&result->point);
      ScreenToClient(w, &result->point);
      bucket = win_handles[windowObj >> 8];
      for (index = bucket->objectCount - 1; index >= 0; --index)
      {
        object = bucket->objects[index];
        if (object->flags & 2 && PointInRect(&result->point, &object->rect))
          break;
      }

      if (index >= 0)
        result->object = index | windowObj;
      else
        result->object = windowObj;
      if (result->object == 0)
        result->object = 0xff00 | windowObj >> 8;
      return stop;
    }
    else
      return stop;
  }
  else
    return stop;
}

