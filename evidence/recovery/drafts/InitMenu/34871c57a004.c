/* R2 use only imports and public names evidenced by InitMenu packet. */
extern unsigned int far db_LoadObject(int object, int kind, int lock);
extern void far *mem_Lock(unsigned int handle);
extern void far db_UnhookObject(int object, int kind);
extern int near mainRootWnd;
extern unsigned char __based(__segname("PACK")) match_position[];
extern int far pascal CreateMenu(void);
extern int far pascal CreatePopupMenu(void);
extern int far pascal AppendMenu(int menu, int flags, unsigned int item, char far *text);
extern int far pascal SetMenu(int window, int menu);
extern void far mem_free(void far *block);
int far *ms_LoadPopUpResource(int resourceID, int far *count);
int far InitMenu(int object) {
    unsigned int handle;
    int menu;
    int popup;
    int count;
    int i;
    char far **strings;
    handle = db_LoadObject(object, 6, 0);
    if (handle == 0) return 0;
    mem_Lock(handle);
    db_UnhookObject(object, 6);
    menu = CreateMenu();
    popup = CreatePopupMenu();
    strings = (char far **)ms_LoadPopUpResource(match_position[0x7260], &count);
    for (i = 0; i != count; i = i + 1) AppendMenu(popup, 0x400, match_position[0x7262 + i], strings[i]);
    AppendMenu(menu, 0x10, popup, (char far *)&match_position[0x7276]);
    SetMenu(mainRootWnd, menu);
    return menu;
}