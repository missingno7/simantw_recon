/* The object kind is stored as a signed byte at offset 0x21. */
/*
 * win_DrawTitle: scan a window's child objects for a title-bearing object
 * (a static-text object, type 12, whose text is stored inline; or an
 * editable-text object, type 18, whose text is reached through an
 * indirect far pointer) and push whichever title text was found to the
 * real Windows control via SetWindowText.
 */
struct WinObjHdr {
    unsigned char pad0[0x21];
    char type;
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
    struct WinObjHdr far *obj;
    struct WinBucket far *bucket;
    struct WinObjHdr far * far *p;
    char far *text;
    int n;
    text = 0;
    win_LockWin(objectNumber);
    bucket = win_handles[objectNumber >> 8];
    n = bucket->numChildren;
    p = bucket->objects;
    if (n > 0) {
        do {
            obj = *p++;
            switch (obj->type) {
            case 12: text = (char far *)&obj->data; break;
            case 18: {
                char far * far *indirect = obj->data.indirectPtr;
                if (indirect) text = *indirect;
                break;
            }
            }
        } while (--n);
    }
    win_UnlockWin(objectNumber);
    if (text) SetWindowText(win_hwnd[objectNumber >> 8], text);
}
