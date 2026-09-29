/*
 * ToggleHistButton(msg): toggles graphing of one of the (up to 10)
 * history-line buttons (msg 0x1503..0x150c, index = msg-0x1503) on/off.
 * A private per-button byte flag (((unsigned char far *)editBufInvalidFlag)[idx+0x8e38], i.e. es:[si-0x71c8])
 * records whether that line is currently graphed. If it was OFF (flag
 * 0), the line is turned ON: the flag is set, and if the active-colony
 * list ((unsigned char far *)editBufInvalidFlag)[0x8e54..0x8e5c) (the same 4-slot list ProcHistoryEvent/
 * HistUpdate graph) is full (its bitmask word at ((unsigned char far *)editBufInvalidFlag)[0x8e5c] has no free
 * bit for this index... -- actually the eviction candidate is the slot
 * pointed to by ((unsigned char far *)editBufInvalidFlag)[0x8e5a]), the button occupying the evicted slot is
 * unselected (win_MakeObjUnselected) and its own bit cleared, then the
 * list is shifted right by one slot (memmove) and the new index inserted
 * at ((unsigned char far *)editBufInvalidFlag)[0x8e54]. If it was ON (flag nonzero), the line is turned OFF:
 * its slot is located in the active list and removed via memmove
 * (shifting the remaining entries down). Either way, the window is
 * redrawn: MSClipStart(win_hwnd[21]), win_FillObjRect(0x150e,
 * ConvColor(0)), then drawHistGraph(value,0,i) for each non-sentinel
 * (0x8000) active-list entry, MSClipEnd(), clip_Off(). clip_SetWin(0x1500)
 * guards the whole function.
 */
extern int far editBufInvalidFlag[];
extern unsigned char far Dx8[];

extern void far clip_SetWin(int window);
extern void far clip_Off(void);
extern void far MSClipStart(int window);
extern void far MSClipEnd(void);
extern int far ConvColor(int color);
extern void far win_FillObjRect(int object, int color);
extern void far drawHistGraph(int value, int flag, int index);
extern void far win_MakeObjUnselected(int object);
extern void far memmove(void far *dst, void far *src, unsigned n);

extern int near win_hwnd[];

void far ToggleHistButton(int msg)
{
    int idx;
    int i;
    int evict;
    register unsigned int p;
    int v;
    int bit;

    clip_SetWin(0x1500);

    idx = msg - 0x1503;

    if (((unsigned char far *)editBufInvalidFlag)[0x42 + idx] != 0) {
        i = 0;
        for (; i < 4; ++i) {
            if (((unsigned int far *)Dx8)[0x472a + i] == idx)
                goto remove_found;
        }
        goto removal_done;
remove_found:
        memmove(&((unsigned int far *)Dx8)[0x472a + i],
                &((unsigned int far *)Dx8)[0x472b + i], (4 - i) * 2);
        editBufInvalidFlag[0x32] = 0x8000;
removal_done:
        ((unsigned char far *)editBufInvalidFlag)[0x42 + idx] = 0;
        editBufInvalidFlag[0x33] |=
            1 << ((unsigned char far *)editBufInvalidFlag)[0x1a + idx * 2];
    } else {
        ((unsigned char far *)editBufInvalidFlag)[0x42 + idx] = 1;
        evict = editBufInvalidFlag[0x32];
        if (evict != 0x8000) {
            ((unsigned char far *)editBufInvalidFlag)[0x42 + evict] = 0;
            win_MakeObjUnselected(evict + 0x1503);
            editBufInvalidFlag[0x33] |=
                1 << ((unsigned char far *)editBufInvalidFlag)[0x1a + evict * 2];
        }
        memmove(&((unsigned int far *)Dx8)[0x472b],
                &((unsigned int far *)Dx8)[0x472a], 6);
        ((unsigned int far *)Dx8)[0x472a] = idx;
        i = 0;
        bit = 1;
find_free_slot:
        if ((editBufInvalidFlag[0x33] & bit) != 0)
            goto free_slot_found;
        bit <<= 1;
        ++i;
        if (i < 4)
            goto find_free_slot;
        goto slot_allocation_done;
free_slot_found:
        editBufInvalidFlag[0x33] &= ~bit;
        editBufInvalidFlag[0x0d + idx] = i;
slot_allocation_done:
        ;
    }

    MSClipStart(win_hwnd[21]);
    win_FillObjRect(0x150e, ConvColor(0));
    for (i = 0, p = 0x8e54; p < 0x8e5c; p += 2, i++) {
        v = *(int far *)&((unsigned char far *)editBufInvalidFlag)[p];
        if (v != (int)0x8000)
            drawHistGraph(v, 0, i);
    }
    MSClipEnd();
    clip_Off();
}
