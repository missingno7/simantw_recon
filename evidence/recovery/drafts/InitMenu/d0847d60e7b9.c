/* InitMenu: rebase the database's far-pointer lists, then turn its title and
   item tables into Win16 menus, including separator and nested resource rows. */
typedef union {
    void far *pointer;
    unsigned long bits;
} MENU_FAR_VALUE;

typedef struct {
    void far *entry;
} MENU_FAR_ENTRY;

extern unsigned int far db_LoadObject(int object, int kind, int lock);
extern void far *near mem_Lock(unsigned int handle);
extern void far db_UnhookObject(int object, int kind);
extern void near mem_free(void far *block);
extern int near mainRootWnd;
extern unsigned char __based(__segname("PACK")) match_position[];
extern int far pascal CreateMenu(void);
extern int far pascal CreatePopupMenu(void);
extern int far pascal AppendMenu(int menu, int flags, unsigned int item, char far *text);
extern int far pascal SetMenu(int window, int menu);
extern char far * far strchr(char far *text, int ch);
extern int far atoi(char far *text);
extern char far * far * ms_LoadPopUpResource(int resourceID, int far *count);

static void far * volatile lockedMenuData;
static unsigned int volatile popupMenuIndex;

int far InitMenu(int object)
{
    unsigned int handle;
    unsigned int rootMenu;
    unsigned int currentMenu;
    unsigned int groupIndex;
    unsigned int itemIndex;
    unsigned int nestedIndex;
    unsigned int itemId;
    unsigned int savedGroup;
    unsigned int savedItem;
    unsigned int resourceCount;
    unsigned int row;
    unsigned int slotOffset;
    void far *data;
    unsigned long far *outer;
    unsigned long far *inner;
    char far * far *titles;
    char far * far *groups;
    char far **items;
    char far *text;
    char far *mark;
    char far **resourceItems;
    char far *resourceText;
    MENU_FAR_VALUE base;
    MENU_FAR_VALUE relative;

    handle = db_LoadObject(object, 6, 0);
    if (handle != 0) {
        data = mem_Lock(handle);
        lockedMenuData = data;
        db_UnhookObject(object, 6);

        base.pointer = data;
        outer = (unsigned long far *)data;
        while (*outer != 0) {
            *outer = *outer + base.bits;
            relative.bits = *outer;
            inner = (unsigned long far *)relative.pointer;
            while (*inner != 0) {
                *inner = *inner + base.bits;
                inner++;
            }
            outer++;
        }

        rootMenu = CreateMenu();
        *(unsigned int far *)(match_position + 0x7260) = rootMenu;
        groupIndex = 0;
        data = lockedMenuData;
        titles = (char far * far *)*(unsigned long far *)data;
        if (titles != 0 && *titles != 0) {
            do {
                slotOffset = 0x7262 + groupIndex * 2;
                currentMenu = CreateMenu();
                *(unsigned int far *)(match_position + slotOffset) = currentMenu;
                groups = (char far * far *)((char far *)data + 4);
                groups += groupIndex;
                items = (char far **)groups[groupIndex];
                itemIndex = 0;
                if (items != 0 && *items != 0) {
                    do {
                        text = *items;
                        if (*text == '-') {
                            itemId = (unsigned int)((groupIndex << 4) + itemIndex - 0x2ff);
                            AppendMenu(currentMenu, 0x800, itemId, (char far *)0);
                        } else {
                            mark = strchr(text, 0x23);
                            if (mark != 0) {
                                *mark = 0;
                                resourceCount = 0;
                                resourceItems = ms_LoadPopUpResource(atoi(mark + 1), &resourceCount);
                                if (resourceItems != 0 && resourceCount != 0) {
                                    nestedIndex = popupMenuIndex;
                                    slotOffset = 0x7276 + nestedIndex * 2;
                                    currentMenu = *(unsigned int far *)(match_position + (0x7262 + groupIndex * 2));
                                    *(unsigned int far *)(match_position + slotOffset) = CreatePopupMenu();
                                    for (row = 0; row < resourceCount; row++) {
                                        resourceText = resourceItems[row] + 1;
                                        itemId = (unsigned int)(((nestedIndex | 0xff90) << 4) | (row + 1));
                                        if (*resourceText == '-')
                                            AppendMenu(*(unsigned int far *)(match_position + slotOffset), 0x800, itemId, (char far *)0);
                                        else
                                            AppendMenu(*(unsigned int far *)(match_position + slotOffset), 0, itemId, resourceText);
                                    }
                                    mem_free(resourceItems);
                                    AppendMenu(currentMenu, 0x10,
                                        *(unsigned int far *)(match_position + slotOffset), text);
                                    popupMenuIndex++;
                                } else {
                                    itemId = (unsigned int)((groupIndex << 4) + itemIndex - 0x2ff);
                                    AppendMenu(currentMenu, 0, itemId, text);
                                    if (resourceItems != 0)
                                        mem_free(resourceItems);
                                }
                            } else {
                                itemId = (unsigned int)((groupIndex << 4) + itemIndex - 0x2ff);
                                AppendMenu(currentMenu, 0, itemId, text);
                            }
                        }
                        items++;
                        itemIndex++;
                    } while (*items != 0);
                }
                AppendMenu(rootMenu, 0x10, currentMenu, *titles);
                titles++;
                groupIndex++;
            } while (*titles != 0);
        }
        SetMenu(mainRootWnd, rootMenu);
    }
    return 1;
}
