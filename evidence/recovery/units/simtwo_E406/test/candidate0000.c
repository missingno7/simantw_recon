/* Candidate translation unit simtwo_E406: composed from preserved exact-body sources
 * in MAPSYM order. Internal evidence id, not a historical filename.
 * Members: _win_AutoSize */

struct BitmapSize {
    int width;
    int height;
};
typedef struct BitmapSize BitmapSize;
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
    int left;
    int top;
    int right;
    int bottom;
    unsigned char pad0[0x19];
    char type;
    unsigned char pad1[0x28 - 0x22];
    union {
        int bitmap;
        char text[4];
    } u1;
    char text2[4];
};
static struct BitmapSize near AutoSizeResult;

BitmapSize far win_AutoSize(struct WinObj far *obj)
{
    struct BitmapSize temp;

    switch (obj->type) {
    case 5:
    case 12:
        temp.width = font_StringWidth(obj->u1.text);
        temp.height = font_FontHeight();
        AutoSizeResult = temp;
        AutoSizeResult.width += 8;
        AutoSizeResult.height += 8;
        break;
    case 6:
    case 13:
        gr_BitMapSize(&AutoSizeResult, obj->u1.bitmap);
        break;
    case 9:
        temp.width = font_StringWidth(obj->u1.text);
        temp.height = font_FontHeight();
        AutoSizeResult = temp;
        break;
    case 16:
    case 18:
        temp.width = font_StringWidth(obj->text2);
        temp.height = font_FontHeight();
        AutoSizeResult = temp;
        break;
    case 17:
        temp.width = font_StringWidth(obj->text2);
        temp.height = font_FontHeight();
        AutoSizeResult = temp;
        AutoSizeResult.width += 8;
        AutoSizeResult.height += 8;
        break;
    default:
        AutoSizeResult.width = obj->right - obj->left;
        AutoSizeResult.height = obj->bottom - obj->top;
        break;
    }
    return AutoSizeResult;
}

