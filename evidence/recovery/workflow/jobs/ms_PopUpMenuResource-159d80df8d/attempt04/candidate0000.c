/* Load a popup definition, append each decoded item, position it at the caller's point, track it, and return the selected menu ID while updating the caller's selection byte. */
struct MenuPoint {
    int x;
    int y;
};

extern int near rootWnd;
extern char far *near ms_LoadPopUpResource(int resourceID, int far *count);
extern void near mem_free(void far *block);
extern int far MyGetTopWindow(int window);
extern int far popUpMenuId;
extern unsigned int far pascal CreatePopupMenu(void);
extern int far pascal AppendMenu(unsigned int menu, unsigned int flags,
                                 unsigned int item, char far *text);
extern int far pascal ClientToScreen(unsigned int window,
                                     struct MenuPoint far *point);
extern int far pascal TrackPopupMenu(unsigned int menu, unsigned int flags,
                                     int x, int y, int reserved,
                                     unsigned int window, void far *rect);
extern int far pascal DestroyMenu(unsigned int menu);

int far ms_PopUpMenuResource(int x, int y, int resourceID,
                             char far *selection)
{
    int count;
    char far * far *items;
    char far * far *cursor;
    unsigned int menu;
    int index;
    unsigned int item;
    char far *itemText;
    struct MenuPoint point;

    items = (char far * far *)ms_LoadPopUpResource(resourceID, &count);
    if (count <= 0)
        goto no_selection;
    if ((unsigned char)*selection > count)
        *selection = (char)0xff;
    menu = CreatePopupMenu();
    index = 0;
    if (count <= 0) {
        mem_free(items);
        goto show_menu;
    }
    cursor = items;
    for (; index < count; index++, cursor++) {
        item = (unsigned int)((index + 1) | 0xf900);
        itemText = *cursor + 1;
        if (*itemText == '-')
            AppendMenu(menu, 0x800, item, (char far *)0);
        else
            AppendMenu(menu, 0, item, itemText);
    }
    mem_free(items);
show_menu:
    point.x = x;
    point.y = y;
    ClientToScreen(MyGetTopWindow(rootWnd), &point);
    popUpMenuId = 0;
    if (!TrackPopupMenu(menu, 0, point.x, point.y, 0,
                        MyGetTopWindow(rootWnd), (void far *)0)) {
        DestroyMenu(menu);
        goto no_selection;
    }
    DestroyMenu(menu);
    if (popUpMenuId == 0)
        goto no_selection;
    *selection = (char)popUpMenuId;
    return popUpMenuId;
no_selection:
    return 0;
}

