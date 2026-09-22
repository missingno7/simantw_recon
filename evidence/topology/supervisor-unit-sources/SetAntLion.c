/* SetAntLion: place ant lion `index` on the map (tile 0x38 + its type).
 *
 * Unit review (simtwo:3EF8): the isolated candidate had named the three lion
 * arrays antLionX/antLionY/antLionType; the objects are the MAPSYM publics
 * LionListX, LionListY and LionListT, exactly as the admitted unit spells them. */
extern unsigned char far LionListX[];
extern unsigned char far LionListY[];
extern unsigned char far LionListT[];
extern void far SetMap(int plane, int x, int y, int tile);

void SetAntLion(int index)
{
    SetMap(1, LionListX[index], LionListY[index], LionListT[index] + 0x38);
}
