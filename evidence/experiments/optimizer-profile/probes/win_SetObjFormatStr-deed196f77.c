/*
 * win_SetObjFormatStr: format a printf-style string for a window object
 * into its cached format-object storage.  The object bucket/table follow
 * the admitted win_ObjAddr (Punt "Attempt to get obj address outsize
 * window" on an out-of-range low byte); the object's far pointer at
 * +0x2c names a "format object" whose own far pointer at +0x2a/+0x2c is
 * the growable string buffer and whose bytes from +0x2e are the printf
 * format.  vsprintf builds the text into a local stack buffer; if the
 * growable buffer is unallocated, Ralloc(1,len+8,"formatStr") creates it,
 * otherwise its current size is checked and RallocRealloc(1,len+4) grows
 * it only if needed; either way the formatted text is copied into it.
 */
struct WinBucket {
    unsigned char header[0xc];
    int count;
    unsigned char rest[0x2c - 0xe];
    unsigned char far *objects[256];
};

struct FormatObject {
    unsigned char reserved[0x2a];
    char far *buf;
    char fmt[1];
};

extern struct WinBucket far * near win_handles[];
extern void far win_LockWin(int objectNumber);
extern void far win_UnlockWin(int objectNumber);
extern void far Punt(char far *message, ...);
extern int far vsprintf(char far *buffer, char far *format, void far *args);
extern int far strlen(char far *s);
extern int far strcpy(char far *dst, char far *src);
extern unsigned int far RallocSize(char far *block);
extern char far *Ralloc(int zero, unsigned long size, char far *tag);
extern char far *RallocRealloc(char far *block, int zero, unsigned long size, char far *tag);

void far win_SetObjFormatStr(int objectNumber, char far *format, void far *args)
{
    struct WinBucket far *bucket;
    struct FormatObject far *obj;
    struct FormatObject far *fmtObj;
    char buf[0x74];
    int len;

    win_LockWin(objectNumber);
    bucket = win_handles[objectNumber >> 8];
    if (bucket->count <= (unsigned char)objectNumber)
        Punt("Attempt to get obj address outsize window");
    obj = (struct FormatObject far *)bucket->objects[(unsigned char)objectNumber];
    fmtObj = *(struct FormatObject far * far *)&obj->buf;
    vsprintf(buf, fmtObj->fmt, args);
    len = strlen(buf) + 1;
    if (fmtObj->buf == 0) {
        fmtObj->buf = Ralloc(1, (unsigned long)(len + 8), "formatStr");
    } else if ((int)(RallocSize(fmtObj->buf) + 1) < len) {
        fmtObj->buf = RallocRealloc(fmtObj->buf, 1, (unsigned long)(len + 4), "formatStr");
    }
    strcpy(fmtObj->buf, buf);
    win_UnlockWin(objectNumber);
}
