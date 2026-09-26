struct Rect { int left; int top; int right; int bottom; };
extern unsigned char near displayType;
extern int near _foreColor;
extern void far GSetAttrib(int, int, int);
extern void far GPatBox(int, int, int, int, unsigned int);
extern void far GRectPartialOutline(struct Rect far *, int, unsigned char, int);
void far GRectPartialMixedOutline(struct Rect far *rect, int thick, unsigned char sides, int foreColor, int backColor) { if (!thick) { GRectPartialOutline(rect, thick, sides, foreColor); return; } if ((foreColor != backColor) && (displayType & 1)) { GSetAttrib(foreColor, backColor, 0x20);
    if (sides & 2) GPatBox(rect->left + thick, rect->top + thick, rect->right - thick, rect->top, (((_foreColor >> 8) + 0x10) << 8) | 0x20);
    if (sides & 8) GPatBox(rect->left + thick, rect->bottom - thick, rect->right - thick, rect->bottom, (((_foreColor >> 8) + 0x10) << 8) | 0x20);
    if (sides & 1) GPatBox(rect->left + thick, rect->top, rect->left, rect->bottom, (((_foreColor >> 8) + 0x10) << 8) | 0x20);
    if (sides & 4) { GPatBox(rect->right, rect->top, rect->right - thick, rect->bottom, (((_foreColor >> 8) + 0x10) << 8) | 0x20); return; }
 } GRectPartialOutline(rect, thick, sides, foreColor); }
