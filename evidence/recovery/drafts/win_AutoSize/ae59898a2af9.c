struct BitmapSize { int width; int height; };
extern void far gr_BitMapSize(struct BitmapSize far *size, int bitmap);
extern int far font_StringWidth(char far *string);
extern int far font_FontHeight(void);
struct WinObj { int left; int top; int right; int bottom; unsigned char pad0[0x19]; char type; unsigned char pad1[6]; union { int bitmap; char text[4]; } u1; char text2[4]; };
static struct BitmapSize near AutoSizeResult;
struct BitmapSize far win_AutoSize(struct WinObj far *obj) {
    register char far *p;
    switch (obj->type) {
    case 5: case 12: p = obj->u1.text; goto width_call;
    case 6: case 13: gr_BitMapSize(&AutoSizeResult, obj->u1.bitmap); break;
    case 9: AutoSizeResult.width = font_StringWidth(obj->u1.text); AutoSizeResult.height = font_FontHeight(); break;
    case 16: case 18: AutoSizeResult.width = font_StringWidth(obj->text2) + 8; AutoSizeResult.height = font_FontHeight() + 8; break;
    case 17: p = obj->text2;
    width_call: AutoSizeResult.width = font_StringWidth(p); AutoSizeResult.height = font_FontHeight(); break;
    default: AutoSizeResult.width = obj->right - obj->left; AutoSizeResult.height = obj->bottom - obj->top; break;
    }
    return AutoSizeResult;
}
