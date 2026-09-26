/* First geometry pass for the centered information panel. */
struct PopupRect {
    int left;
    int top;
    int right;
    int bottom;
};

extern void far win_GetObjRect(int objectNumber, struct PopupRect far *rect);
extern void far clip_Push(void);
extern void far clip_SubInclude(struct PopupRect far *rect);

void far PopUpInfoWindow(int center, int leftInset, int rightInset,
                         int titleId)
{
    struct PopupRect desktop;
    int width;
    int height;
    int halfWidth;
    int left;
    int right;
    int top;
    int bottom;

    leftInset -= 4;
    rightInset += 4;

    win_GetObjRect(0x502, &desktop);
    clip_Push();
    clip_SubInclude(&desktop);

    width = desktop.right - desktop.left;
    height = desktop.bottom - desktop.top;
    halfWidth = width / 2;
    left = center - halfWidth + desktop.left;
    right = center + halfWidth + desktop.left;
    top = desktop.top + 4;
    bottom = top + height;

    if (left < desktop.left + 4) {
        left = desktop.left + 4;
        right = left + width / 2 + 8;
    }
    if (right > desktop.right - 4) {
        right = desktop.right - 4;
        left = right - width / 2 - 8;
    }

    /* The record loading and modal event loop follow this geometry setup. */
}
