/*
 * KillAntLion: remove ant lion number index.  Its map cell (plane 1,
 * LionListX/LionListY) is set to the empty code 0x3f; then, addressing
 * the far LionIndex count through a far pointer local that is stored once
 * and reloaded after the copies (as in the admitted win_YardClosed), the
 * count is decremented and the entries above the removed one are shifted
 * down in the five parallel far lists (X, Y, type, mode, stamina).
 */
extern unsigned char far LionListX[];
extern unsigned char far LionListY[];
extern unsigned char far LionListT[];
extern unsigned char far LionListM[];
extern unsigned char far LionListS[];
extern int far LionIndex;

extern void far SetMap(int plane, int x, int y, int value);

void far KillAntLion(int index)
{
    struct { int far * volatile p; } h;
    int i;

    SetMap(1, LionListX[index], LionListY[index], 0x3f);
    h.p = &LionIndex;
    if (*h.p > 0) {
        (*h.p)--;
        for (i = index; i < *h.p; i++) {
            LionListX[i] = LionListX[i + 1];
            LionListY[i] = LionListY[i + 1];
            LionListT[i] = LionListT[i + 1];
            LionListM[i] = LionListM[i + 1];
            LionListS[i] = LionListS[i + 1];
        }
    }
}
