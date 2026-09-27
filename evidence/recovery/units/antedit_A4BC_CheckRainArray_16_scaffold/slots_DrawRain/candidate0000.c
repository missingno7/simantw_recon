/*
 * DrawRain: scatter the rain animation objects over the yard.  A private
 * uninitialised near array of object handles (DGROUP 0xcb04..0xcb1f, zero
 * fixture bytes, no MAPSYM name) is walked from its end with a
 * pre-decrementing pointer while a counter of 14 runs down (the decrement
 * is part of the loop condition, since the entry jump lands on it).  Each
 * drop gets a random position: right = SRand1(400) + 50, bottom =
 * SRand1(150).  An existing handle (not -1) is repositioned with
 * hanim_SetObjectPos(right, bottom, 0x1b5d, yardAnimHandle, handle, 0x8000);
 * otherwise a new object is added with hanim_AddAnimObject(yardAnimHandle,
 * right, bottom, 0x1b5d, 1000) and its handle stored.  Prototypes follow
 * the admitted DrawForSale/DrawSimBird siblings.
 */
extern int near yardAnimHandle;
extern int far SRand1(int range);
extern int far hanim_SetObjectPos(int right, int bottom, int size,
                                  int animation, int object, int layer);
extern int far hanim_AddAnimObject(int animation, int right, int bottom,
                                   int size, int layer);

static int near rainObjects[14];

void far DrawRain(void)
{
    int right;
    int bottom;
    int i;
    int near *drop;

    i = 14;
    drop = rainObjects + 14;
    while (drop--, i--) {
        right = SRand1(400) + 50;
        bottom = SRand1(150);
        if (*drop != -1)
            hanim_SetObjectPos(right, bottom, 0x1b5d, yardAnimHandle,
                               *drop, 0x8000);
        else
            *drop = hanim_AddAnimObject(yardAnimHandle, right, bottom,
                                        0x1b5d, 1000);
    }
}
