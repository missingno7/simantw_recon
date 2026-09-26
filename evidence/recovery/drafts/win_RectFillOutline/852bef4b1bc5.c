struct WinRect { int left; int top; int right; int bottom; };
extern void far win_RectFill(struct WinRect far *rect);
extern void far GRectOutline(struct WinRect far *rect, int third);
void far win_RectFillOutline(struct WinRect far *rect, int third) { win_RectFill(rect); GRectOutline(rect, third); }
