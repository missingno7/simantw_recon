/*
 * GoInNest: migrate the generic "A" list record at index into the
 * colour-specific B or R list (colour<0x40 selects B, else R) at grid
 * position life, then clear that A record and the LifeA display cell.
 * If the destination list (ListIndexB/ListIndexR) is at its 500-entry
 * cap, CompactListB/CompactListR first squeezes out dead records; if it
 * is still full afterward the call does nothing further.  Otherwise
 * AddAntToBList/AddAntToRList(life, 1, (Dx8[index+0x2f62]&0xf8)+4,
 * Dx8[index+0x2b78], Dx8[index+0x334c]) inserts the migrated record
 * (attribute/state/direction sourced from the A list's type/mode/
 * stamina fields), and if HoleMapB/HoleMapR[life] is set,
 * DigTileB/DigTileR(life, 1) digs the destination tile.  Dx8 is the
 * same shared far ant-record object used throughout this corpus; its
 * generic-A-list field offsets here (0x334c stamina, 0x2b78 mode,
 * 0x2f62 type) are new evidence.  This is a near (same-segment) helper,
 * unlike the far B/R colony routines that call it.
 */
extern int far ListIndexB;
extern int far ListIndexR;
extern unsigned char far Dx8[];
extern unsigned char far HoleMapB[];
extern unsigned char far HoleMapR[];
extern unsigned char near LifeA[];
extern void far CompactListB(void);
extern void far CompactListR(void);
extern void far AddAntToBList(int life, int column, int attribute, int state, int direction);
extern void far AddAntToRList(int life, int column, int attribute, int state, int direction);
extern void far DigTileB(int x, int y);
extern void far DigTileR(int x, int y);

void near GoInNest(int colour, int life, int index)
{
    if (colour < 0x40) {
        if (ListIndexB >= 500)
            CompactListB();
        if (ListIndexB >= 500)
            return;
        AddAntToBList(life, 1, (Dx8[index + 0x2f62] & 0xf8) + 4, Dx8[index + 0x2b78], Dx8[index + 0x334c]);
        if (HoleMapB[life] != 0)
            DigTileB(life, 1);
    } else {
        if (ListIndexR >= 500)
            CompactListR();
        if (ListIndexR >= 500)
            return;
        AddAntToRList(life, 1, (Dx8[index + 0x2f62] & 0xf8) + 4, Dx8[index + 0x2b78], Dx8[index + 0x334c]);
        if (HoleMapR[life] != 0)
            DigTileR(life, 1);
    }
    Dx8[index + 0x2f62] = 0;
    LifeA[(colour << 6) + life] = 0;
}
