/*
 * Hypothesis from the selector and field evidence: the high byte of the
 * encoded window id selects win_handles; its window record stores the number
 * of object slots at 0x0c and far object pointers beginning at 0x2c.  Search
 * those slots from the last index down, test the object's 0x24 flag byte,
 * and use PointInRect against the supplied far point.  A hit preserves the
 * window id and ORs in the matching slot index.
 */
struct FindPoint {
    int x;
    int y;
};

struct FindObjectRecord {
    unsigned char reserved[0x24];
    unsigned char flags;
};

struct FindWindow {
    unsigned char reserved0[0x0c];
    int objectCount;
    unsigned char reserved1[0x1e];
    struct FindObjectRecord far *objects[256];
};

extern struct FindWindow far * near win_handles[];
extern int far PointInRect(struct FindPoint far *point,
                           struct FindObjectRecord far *object);

int far win_FindObject(int object, struct FindPoint far *point)
{
    int index;
    struct FindWindow far *window;
    struct FindObjectRecord far *record;

    window = win_handles[object >> 8];
    index = window->objectCount - 1;
    if (index >= 0) {
        do {
            record = window->objects[index];
            if ((record->flags & 2) != 0) {
                if (PointInRect(point, record))
                    return object | index;
            }
            index--;
        } while (index >= 0);
    }
    return object;
}
