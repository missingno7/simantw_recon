/*
 * win_DrawTitle: scan a window's child objects for a title-bearing object
 * (a static-text object, type 12, whose text is stored inline; or an
 * editable-text object, type 18, whose text is reached through an
 * indirect far pointer) and push whichever title text was found to the
 * real Windows control via SetWindowText.
 */
struct WinObjHdr {
    unsigned char pad0[0x21];
    unsigned char type;
    unsigned char pad1[8];
    union {
        char text[1];
        char far * far *indirectPtr;
    } data;
};

struct WinBucket {
    unsigned char pad0[0xc];
    int numChildren;
    unsigned char pad1[30];
    struct WinObjHdr far *objects[256];
};

extern struct WinBucket far * near win_handles[];
extern int near win_hwnd[];
extern void far win_LockWin(int objectNumber);
extern void far win_UnlockWin(int objectNumber);
extern int far pascal SetWindowText(int hwnd, char far *text);

void far win_DrawTitle(int objectNumber)
{
    struct WinBucket far *bucket;
    struct WinObjHdr far *obj;
    struct WinObjHdr far * far *p;
    char far *text;
    int n;

    text = 0;
    win_LockWin(objectNumber);
    bucket = win_handles[objectNumber >> 8];
    if (bucket->numChildren > 0) {
        p = bucket->objects;
        n = bucket->numChildren;
        do {
            obj = *p;
            if (obj->type == 12) {
                text = (char far *)&obj->data;
            } else if (obj->type == 18) {
                if (obj->data.indirectPtr)
                    text = *obj->data.indirectPtr;
            }
            p++;
        } while (--n);
    }
    win_UnlockWin(objectNumber);
    if (text)
        SetWindowText(win_hwnd[objectNumber >> 8], text);
}
