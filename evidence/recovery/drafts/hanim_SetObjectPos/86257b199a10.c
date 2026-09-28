struct HanimSet {
    int count;
    unsigned int objects;
    int capacity;
    int nextObjectId;
};
struct HanimObject {
    unsigned char flag0;
    unsigned char reserved1;
    unsigned char reserved2;
    unsigned char dirty3;
    unsigned char dirty4;
    unsigned char dirty5;
    int reserved06;
    int reserved08;
    int reserved0a;
    int reserved0c;
    int left;
    int top;
    int right;
    int bottom;
    int x;
    int y;
    int width;
    int height;
    int reserved1e;
    int objectNumber;
    unsigned int bitmapHandle;
    int cachedExtent;
    int bitmapCode;
    void far *bitmapData;
};
struct BitmapSize { int width; int height; };

extern int near rootWnd;
extern void far *mem_Lock(unsigned int handle);
extern int far mem_Unlock(unsigned int handle);
extern int far hanim_AddAnimObject(int animation, int x, int y,
                                   int bitmap, int layer);
extern int far sprintf(char far *buffer, char far *format, ...);
extern int far pascal MessageBox(int window, char far *text,
                                 char far *caption, unsigned style);

extern void far gr_BitMapSize(struct BitmapSize far *size, int bitmap);

/* These private selector names remain hypotheses from the observed BF74/BF76 accesses. */
extern struct BitmapSize far * far yardBalloonPtr;
extern struct HanimObject far * far lastAddedPtr;
extern char far animEmptySetMessage[];
extern char far animEmptySetCaption[];
extern char far animObjectFormat[];
extern char far animObjectCaption[];

volatile int hanim_SetObjectPos(int x, int y, int bitmap, int animation, int objectNumber, int layer)
{
    struct HanimSet far *set;
    struct HanimObject far *objects;
    struct HanimObject far *object;
    struct BitmapSize size;
    char message[0x100];
    unsigned int tableHandle;
    unsigned int far *handleField;
    int index;
    int count;
    int bitmapCode;
    int addedIndex;
    int changed;

    set = (struct HanimSet far *)mem_Lock(animation);
    count = set->count;
    handleField = &set->objects;
    tableHandle = *handleField;
    objects = (struct HanimObject far *)mem_Lock(tableHandle);

    index = 0;
    while (index < set->count && objects[index].objectNumber != objectNumber)
        ++index;

    if (index >= count) {
        if (count == 0) {
            MessageBox(rootWnd, animEmptySetMessage,
                       animEmptySetCaption, 0x1010);
            mem_Unlock(tableHandle);
            mem_Unlock(animation);
            return;
        }

        mem_Unlock(*handleField);
        mem_Unlock(animation);

        /* The dialog may have allowed the table to change, so search again. */
        set = (struct HanimSet far *)mem_Lock(animation);
        count = set->count;
        tableHandle = set->objects;
        objects = (struct HanimObject far *)mem_Lock(tableHandle);
        index = 0;
        while (index < set->count && objects[index].objectNumber != objectNumber)
            ++index;

        if (index < count) {
            object = &objects[index];
            object->dirty5 = 1;
            object->flag0 = 0;
            while (index < count) {
                objects[index].dirty3 = 1;
                ++index;
            }
        } else {
            sprintf(message, animObjectFormat, objectNumber);
            MessageBox(rootWnd, message, animObjectCaption, 0x1010);
        }

        mem_Unlock(tableHandle);
        mem_Unlock(animation);

        addedIndex = hanim_AddAnimObject(animation, x, y, bitmap, layer);
        set = (struct HanimSet far *)mem_Lock(animation);
        count = set->count;
        handleField = &set->objects;
        tableHandle = *handleField;
        objects = (struct HanimObject far *)mem_Lock(tableHandle);
        index = 0;
        while (index < set->count && objects[index].objectNumber != objectNumber)
            ++index;
        if (index < count)
            objects[index].objectNumber = addedIndex;
        lastAddedPtr->objectNumber = objectNumber;
        mem_Unlock(*handleField);
        mem_Unlock(animation);
        return;
    }

    object = &objects[index];

    if (x == (int)0x8000)
        x = object->x;
    else
        object->x = x;
    if (y == (int)0x8000)
        y = object->y;
    else
        object->y = y;

    bitmapCode = bitmap;
    if (bitmapCode == (int)0x8000)
        bitmapCode = object->bitmapCode;

    if (layer == (int)0x8000) {
        layer = object->cachedExtent;
        if (layer == -1) {
            if (bitmapCode >= 0x7530) {
                size.width = yardBalloonPtr->width;
                size.height = yardBalloonPtr->height;
            } else {
                gr_BitMapSize(&size, bitmapCode);
            }
            layer = y + size.height;
        }
    }

    changed = object->bitmapCode != bitmapCode;
    if (changed) {
        object->bitmapCode = bitmapCode;
        if (bitmapCode >= 0x7530) {
            size.width = yardBalloonPtr->width;
            size.height = yardBalloonPtr->height;
        } else {
            gr_BitMapSize(&size, bitmapCode);
        }
        layer = y + size.height;
    } else {
        size.width = object->width;
        size.height = object->height;
    }

    if (((object->width ^ size.width) & 0xfff8) != 0 ||
        object->height != size.height || object->cachedExtent != layer ||
        object->bitmapCode != bitmapCode) {
        changed = 1;
    }

    object->width = size.width;
    object->height = size.height;
    object->cachedExtent = layer;
    object->left = x & 0xfff8;
    object->right = ((object->left + object->width + 0x0f) & 0xfff8);
    object->top = y;
    object->bottom = y + object->height;
    object->dirty4 = 1;

    if (changed) {
        object->dirty5 = 1;
        object->flag0 = 0;
        while (index < count) {
            objects[index].dirty3 = 1;
            ++index;
        }
    }

    mem_Unlock(tableHandle);
    mem_Unlock(animation);
}
