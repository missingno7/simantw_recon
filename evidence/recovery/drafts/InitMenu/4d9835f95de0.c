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
int far InitMenu(int object) {
    unsigned int handle;
    char far *block;
    int menu;
    int popup;
    handle = db_LoadObject(object, 6, 0);
    if (handle != 0) {
        block = (char far *)mem_Lock(handle);
        db_UnhookObject(object, 6);
        menu = CreateMenu();
        popup = CreatePopupMenu();
        AppendMenu(popup, 0x400, match_position[0x7262], block);
        AppendMenu(menu, 0x10, popup, block);
        SetMenu(mainRootWnd, menu);
        return menu;
    }
    return 0;
}