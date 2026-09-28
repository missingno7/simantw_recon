struct CursorPoint {
    int x;
    int y;
};
struct CursorRect {
    int left;
    int top;
    int right;
    int bottom;
};
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
extern int far PointInRect(struct CursorPoint far *point, struct CursorRect far *rect);


/* Preserve the original count while testing its zero-based last slot. */
int far win_FindObject(register int object, struct FindPoint far *point)
{
    struct FindWindow far *window;
    struct FindObjectRecord far *record;
    int index;

    window = win_handles[object >> 8];
    index = window->objectCount;
    --index;
    if (index < 0)
        return object;
    while (index >= 0) {
        record = window->objects[index];
        if ((record->flags & 2) != 0) {
            if (PointInRect(point, record))
                return object | index;
        }
        --index;
    }
    return object;
}
