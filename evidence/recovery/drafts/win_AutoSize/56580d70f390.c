/* Round 1, variant 4: cases16_18_duplicate hypothesis. */
/*
 * win_AutoSize: compute a window object's natural (width, height) from its
 * type byte at offset 0x21, returning the packed BitmapSize result (MSC
 * small-struct-return convention, AX = width, DX = height, matching the
 * target's final "mov ax,[cc5e]; mov dx,[cc60]" before leave/retf). gr_
 * BitMapSize's signature (struct BitmapSize far *size, int bitmap) and the
 * struct itself are established by src/recovered/wf_OpenCasteWindow-
 * 3d435baaee.c / wf_OpenModeWindow-b97cc714f9.c; font_StringWidth/
 * font_FontHeight by src/recovered/wf_gr_CenterStrInRect-59694d56d6.c. The
 * private per-call scratch at DS 0xcc5e/0xcc60 (no MAPSYM name; the unit
 * simtwo:E406 has win_AutoSize as its sole public) is this function's own
 * static result, matching the observed literal DS-relative addressing (no
 * far selector/relocation).
 *
 * Types 5/9/12 measure a text field embedded at object offset 0x28 (union
 * with a bitmap handle word for 6/13, since gr_BitMapSize reads that same
 * offset's value rather than its address). Types 16/17/18 measure a second
 * text field at offset 0x2c; 16/18 additionally pad both dimensions by 8.
 * Any other type (including out of range) falls back to the object's own
 * rectangle at offset 0 (left, top, right, bottom words): width = right -
 * left, height = bottom - top.
 */
struct BitmapSize {
    int width;
    int height;
};

extern void far gr_BitMapSize(struct BitmapSize far *size, int bitmap);
extern int far font_StringWidth(char far *string);
extern int far font_FontHeight(void);

struct WinRect {
    int left;
    int top;
    int right;
    int bottom;
};

struct WinObj {
    unsigned char pad0[0x21];
    char type;
    unsigned char pad1[0x28 - 0x22];
    union {
        int bitmap;
        char text[4];
    } u1;
    char text2[4];
};

static struct BitmapSize near AutoSizeResult;

struct BitmapSize far win_AutoSize(struct WinObj far *obj)
{
    struct WinRect far *rect;
    char far *p;

    switch (obj->type) {
    case 5:
    case 12:
        p = obj->u1.text;
        goto callWidth;
    case 6:
    case 13:
        gr_BitMapSize(&AutoSizeResult, obj->u1.bitmap);
        break;
    case 9:
        AutoSizeResult.width = font_StringWidth(obj->u1.text);
        AutoSizeResult.height = font_FontHeight();
        break;
    case 16:
        AutoSizeResult.width = font_StringWidth(obj->text2) + 8;
        AutoSizeResult.height = font_FontHeight() + 8;
        break;
    case 18:
        AutoSizeResult.width = font_StringWidth(obj->text2) + 8;
        AutoSizeResult.height = font_FontHeight() + 8;
        break;
    case 17:
        p = obj->text2;
    callWidth:
        AutoSizeResult.width = font_StringWidth(p);
        AutoSizeResult.height = font_FontHeight();
        break;
    default:
        rect = (struct WinRect far *)obj;
        AutoSizeResult.width = rect->right - rect->left;
        AutoSizeResult.height = rect->bottom - rect->top;
        break;
    }
    return AutoSizeResult;
}
