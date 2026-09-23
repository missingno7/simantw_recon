/*
 * Add one keyed animation record to a handle-backed set.  The set header
 * follows the verified MakeAnimSet/RemoveAnimSet layout (count, array
 * handle, capacity, next 15-bit object id).  The record stride and key at
 * +0x20 follow verified hanim_FindObject.  Each allocation is locked only
 * while its far record is being updated.
 */
struct HanimSet {
    int count;
    unsigned int objects;
    int capacity;
    int nextObject;
};

struct BitmapSize {
    int width;
    int height;
};

struct AnimObject {
    unsigned char flags[6];
    int state6;
    int state8;
    int statea;
    int statec;
    int left;
    int y;
    int right;
    int bottom;
    int x;
    int yArg;
    int width;
    int height;
    int bitmapBytes;
    int objectId;
    unsigned int bitmap;
    int layer;
    int size;
    unsigned char tail[4];
};

extern void far *mem_Lock(unsigned int handle);
extern int far mem_Unlock(unsigned int handle);
extern unsigned int far mem_Realloc(unsigned int handle, unsigned long bytes,
                                    int kind);
extern unsigned int far mem_Alloc(unsigned long bytes, int kind,
                                  char far *name);
extern void far gr_BitMapSize(struct BitmapSize far *size, int bitmap);
extern void far *memmove(void far *destination, void far *source,
                         unsigned int bytes);
extern int far match_position[];
extern void far *yardBalloonPtr;
extern unsigned char near displayType;

int far hanim_AddAnimObject(int animation, int right, int bottom,
                            int size, int layer)
{
    unsigned int objectHandle;
    struct HanimSet far *set;
    struct AnimObject far *objects;
    struct AnimObject far *object;
    struct BitmapSize bitmapSize;
    int objectId;
    int index;
    int count;
    int left;
    int rowBytes;

    set = (struct HanimSet far *)mem_Lock(animation);
    objectHandle = set->objects;
    count = set->count;
    if (set->capacity == count) {
        set->capacity = count + 2;
        objectHandle = mem_Realloc(objectHandle,
                                   (unsigned long)(set->capacity * 0x2c), 1);
        set->objects = objectHandle;
    }
    objects = (struct AnimObject far *)mem_Lock(objectHandle);
    objectId = set->nextObject & 0x7fff;
    ++set->nextObject;

    for (;;) {
        index = 0;
        while (index < count && objects[index].objectId != objectId)
            ++index;
        if (index == count)
            break;
        objectId = set->nextObject & 0x7fff;
        ++set->nextObject;
    }

    object = objects + count;
    if (size >= 30000) {
        struct BitmapSize far *balloonSize;
        balloonSize = (struct BitmapSize far *)
            ((unsigned char far *)yardBalloonPtr + 8);
        bitmapSize.width = balloonSize->width;
        bitmapSize.height = balloonSize->height;
    } else {
        gr_BitMapSize(&bitmapSize, objectId);
    }

    if (layer == -1)
        layer = bottom + bitmapSize.height;
    index = 0;
    while (index < count && objects[index].layer <= layer)
        ++index;
    object = objects + index;
    if (index < count) {
        memmove(objects + index + 1, object,
                (unsigned int)(count - index) * 0x2c);
        ++set->count;
    } else {
        ++set->count;
    }

    *(unsigned long far *)&match_position[0x3e1f] = (unsigned long)object;
    object->flags[0] = 1;
    object->flags[1] = 0;
    object->flags[3] = 1;
    object->flags[4] = 0;
    object->flags[5] = 0;
    object->left = -1;
    object->state8 = -1;
    object->statea = -1;
    object->statec = -1;
    object->state6 = -1;
    left = right & 0xfff8;
    object->left = left;
    object->right = (left + bitmapSize.width + 15) & 0xfff8;
    object->x = right;
    object->y = bottom;
    object->bottom = bottom + bitmapSize.height;
    object->width = bitmapSize.width;
    object->height = bitmapSize.height;
    object->yArg = bottom;
    object->size = size;
    object->objectId = objectId;
    object->layer = layer;

    if (displayType & 1) {
        rowBytes = ((object->right - left + 7) >> 3) * bitmapSize.height + 4;
    } else if (displayType == 2) {
        rowBytes = ((object->right - left) >> 1) * bitmapSize.height + 4;
    } else {
        rowBytes = (((object->right - left + 7) >> 3) + 1) * 4;
    }
    object->bitmapBytes = rowBytes;
    object->bitmap = mem_Alloc((unsigned long)rowBytes, 1, "anim object");
    mem_Unlock(objectHandle);
    mem_Unlock(animation);
    return objectId;
}
