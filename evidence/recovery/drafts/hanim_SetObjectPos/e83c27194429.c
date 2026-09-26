/*
 * Hypothesis: locate the animation record by its public object number, update
 * its point and bitmap bounds, or create and attach the record if absent.
 * The eight-byte set header and 0x2c record stride follow admitted neighbors.
 */
struct HanimSet {
    int count;
    unsigned int objects;
    int reserved1;
    int reserved2;
};

struct HanimObject {
    unsigned char flag3;
    unsigned char flag4;
    unsigned char flag5;
    unsigned char reserved6[10];
    int left;
    int top;
    int right;
    int bottom;
    int x;
    int y;
    int state;
    int height;
    int reserved1e;
    int objectNumber;
    int reserved22;
    int width;
    int bitmap;
    unsigned char reserved28[4];
};

struct BitmapSize {
    int width;
    int height;
};

extern void far *mem_Lock(unsigned int handle);
extern int far mem_Unlock(unsigned int handle);
extern void far gr_BitMapSize(struct BitmapSize far *size, int bitmap);
extern int far hanim_AddAnimObject(int animation, int right, int bottom,
                                   int size, int layer);

int far hanim_SetObjectPos(int right, int bottom, int bitmap,
                           int animation, int objectNumber, int layer)
{
    struct HanimSet far *set;
    struct HanimObject far *objects;
    struct HanimObject far *object;
    struct BitmapSize size;
    unsigned int tableHandle;
    int index;
    int created;

    set = (struct HanimSet far *)mem_Lock(animation);
    if (set == 0)
        return -1;
    tableHandle = set->objects;
    objects = (struct HanimObject far *)mem_Lock(tableHandle);
    if (objects == 0) {
        mem_Unlock(animation);
        return -1;
    }

    object = (struct HanimObject far *)0;
    for (index = 0; index < set->count; ++index) {
        object = (struct HanimObject far *)
            ((unsigned char far *)objects + (unsigned long)index * 0x2cL);
        if (object->objectNumber == objectNumber)
            break;
    }

    created = 0;
    if (index >= set->count) {
        mem_Unlock(tableHandle);
        mem_Unlock(animation);
        index = hanim_AddAnimObject(animation, right, bottom, bitmap, layer);
        if (index < 0)
            return index;
        created = 1;
        set = (struct HanimSet far *)mem_Lock(animation);
        objects = (struct HanimObject far *)mem_Lock(set->objects);
        object = (struct HanimObject far *)
            ((unsigned char far *)objects + (unsigned long)index * 0x2cL);
        object->objectNumber = objectNumber;
    }

    if (right != (int)0x8000)
        object->x = right;
    if (bottom != (int)0x8000)
        object->y = bottom;
    if (bitmap != (int)0x8000) {
        object->bitmap = bitmap;
        gr_BitMapSize(&size, bitmap);
        object->width = size.width;
        object->height = size.height;
    }
    if (layer != (int)0x8000)
        object->state = layer;

    object->left = object->x;
    object->top = object->y;
    object->right = object->left + object->width;
    object->bottom = object->top + object->height;
    object->flag4 = 1;
    object->flag5 = 1;

    mem_Unlock(set->objects);
    mem_Unlock(animation);
    return created ? index : objectNumber;
}
