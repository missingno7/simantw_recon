/*
 * Hypothesis: edit the scent layer for object 0x10.  The rectangle field
 * accesses prove the historical four-word left/top/right/bottom layout;
 * DoProxMenu receives the menu id, incremented current layer, right+2, and
 * top in that source order, which produces the target's reverse pushes.
 */
struct ScentRect {
    int left;
    int top;
    int right;
    int bottom;
};

extern void far win_GetObjRect(int object, struct ScentRect far *rect);
extern int far win_DoProxMenu(int menu, int layer, int x, int y);
extern void far win_SetObjSelectedState(int object, int selected);
extern void clip_SetWin(int window);
extern void ForceUpdateEdit(void);
extern int near ELayerMode;

void far EditScentMenu(void)
{
    struct ScentRect rect;
    int layer;

    win_GetObjRect(0x10, &rect);
    layer = win_DoProxMenu(0x600, ELayerMode + 1,
                           rect.right + 2, rect.top);
    if (layer == -1)
        return;
    ELayerMode = layer - 1;
    clip_SetWin(0);
    win_SetObjSelectedState(0x10, ELayerMode != -1);
    ForceUpdateEdit();
}
