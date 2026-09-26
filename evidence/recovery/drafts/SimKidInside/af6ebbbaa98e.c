/*
 * SimKidInside: per-tick update for the boy character while indoors.
 * If ForSaleState==1, a small sub-machine (SRand1-based) schedules the
 * boy's next canned message via a MacTickCount-based delay written into
 * the far long BoyMsgCnt, BoyMessOn and BoyMsgOffset -- this only touches
 * the KidState word (Dx8[0x8a86]) when its value is 0x21, selecting a new
 * message-related frame counter (di) from a private near table (three
 * candidates) or moving straight to the common continuation otherwise.
 * Once KidState settles, the outer switch on KidState (0-21) reads one
 * three-field animation record (direction/frame-lo/frame-hi, or for two
 * special "random walk" states a word direction plus two bytes) from a
 * private per-state Dx8-segment table indexed by NodeCnt, feeding the new
 * direction into "di" and the two data bytes into locals later stored as
 * BoyX/BoyY.  States 22-38 run a food/ant-interaction sub-machine that
 * can retire the boy's dead-ant marker via FindInAList/DeadAntHere and
 * possibly kill a spider standing on the same tile.  The common
 * continuation clears/sets BoyHere depending on KidState (0x26 forces it
 * on; 0x14/0x15 conditionally force it on based on NodeCnt), stores
 * BoyX/BoyY/BoyFrame, and -- outside the mystery-house yard mode -- runs
 * a footstep/parity state machine (FootHere/FootTog/BoyDir/BoyPx/BoyPy)
 * that calls FootFall and a footstep sound when the boy's screen pixel
 * position crosses grid boundaries.  Finally, with enough total
 * population (Rpop+Bpop)*8, it may pick a random yard tile via
 * SRand128/SRand64, clear a dead ant there through FindInAList/
 * DeadAntHere/AlistT, and if the tile lands on the spider, KillSpider();
 * on Colony game type with MePlane==1 and a 1-in-4 SRand4 roll, it
 * finally calls YellowDeath(9).
 */
extern int near ForSaleState;
extern unsigned char far Dx8[];
extern int far NodeCnt;
extern long far BoyMsgCnt;
extern int far BoyMessOn;
extern int far BoyMsgOffset;
extern int near BoyHere;
extern int near BoyX;
extern int near BoyY;
extern int near BoyFrame;
extern int near MapMode;
extern int near YardMode;
extern int near BoyDir;
extern int near BoyPx;
extern int near FootHere;
extern int near FootTog;
extern int far CurYardPnt[];
extern int near BoyPy;
extern int far match_position[];
extern int near RpopT;
extern int near BpopT;
extern unsigned char far AlistT[];
extern int near SpidX;
extern int near SpidY;
extern int near CurGameType;
extern int near MePlane;

extern int far SRand1(int range);
extern long far MacTickCount(void);
extern void far myBeginSound(unsigned int first, unsigned int second, unsigned int third);
extern void far FootFall(int px, int py);
extern int far SRand128(void);
extern int far SRand64(void);
extern int far FindInAList(int x, int y);
extern int far DeadAntHere(int x, int y, int flag);
extern void far KillSpider(void);
extern int far SRand4(int range);
extern void far YellowDeath(int cause);

#define KID_STATE (*(int far *)&Dx8[0x8a86])

void far SimKidInside(void)
{
    int far * volatile statePtr = (int far *)&Dx8[0x8a86];
    int di;
    int val1, val2;

    if (ForSaleState == 1) {
        int state = *statePtr;
        int m;
        if (state < 0x1e && ++NodeCnt > Dx8[0x2380 + state]) {
            NodeCnt = 0;
                m = SRand1(3);
                if (m == 0) {
                    long t = MacTickCount() + 0x12c;
                    BoyMsgCnt = t;
                    BoyMessOn = 1;
                    BoyMsgOffset = 0x15;
                } else if (m == 1) {
                    long t = MacTickCount() + 0x12c;
                    BoyMsgCnt = t;
                    BoyMessOn = 1;
                    BoyMsgOffset = 0x16;
                } else {
                    int si = SRand1(3) + 0xf;
                    if (si <= 0x16) {
                        long t = MacTickCount() + 0x12c;
                        BoyMsgCnt = t;
                        BoyMessOn = 1;
                        BoyMsgOffset = si;
                    }
                }
        }
    }

    if (*statePtr >= 0x1e || *statePtr > 0x15) {
        if (*statePtr < 0x27) {
            int si = *statePtr - 0x1e;
            di = *(int far *)&Dx8[0x2576 + si * 2];
            val1 = Dx8[0x2588 + si];
            val2 = Dx8[0x2592 + si];
            if (SRand1(Dx8[0x259c + si]) == 0) {
                *statePtr = Dx8[0x25a6 + si];
                NodeCnt = 0;
            }
        }
        goto continue_common;
    }

    switch (*statePtr) {
    case 0:
        di = *(int far *)&Dx8[NodeCnt + 0x2396] & 0xff;
        val1 = Dx8[NodeCnt + 0x239a];
        val2 = Dx8[NodeCnt + 0x239e];
        break;
    case 1:
        di = *(int far *)&Dx8[NodeCnt + 0x23a2] & 0xff;
        val1 = Dx8[NodeCnt + 0x23a6];
        val2 = Dx8[NodeCnt + 0x23aa];
        break;
    case 2:
        di = *(int far *)&Dx8[NodeCnt + 0x23ae] & 0xff;
        val1 = Dx8[NodeCnt + 0x23c2];
        val2 = Dx8[NodeCnt + 0x23d6];
        break;
    case 3:
        di = *(int far *)&Dx8[NodeCnt + 0x23ea] & 0xff;
        val1 = Dx8[NodeCnt + 0x23fe];
        val2 = Dx8[NodeCnt + 0x2412];
        break;
    case 4:
        di = *(int far *)&Dx8[NodeCnt + 0x2426] & 0xff;
        val1 = Dx8[NodeCnt + 0x242a];
        val2 = Dx8[NodeCnt + 0x242e];
        break;
    case 5:
        di = *(int far *)&Dx8[NodeCnt + 0x2432] & 0xff;
        val1 = Dx8[NodeCnt + 0x2436];
        val2 = Dx8[NodeCnt + 0x243a];
        break;
    case 6:
        di = *(int far *)&Dx8[NodeCnt + 0x243e] & 0xff;
        val1 = Dx8[NodeCnt + 0x244a];
        val2 = Dx8[NodeCnt + 0x2456];
        break;
    case 7:
        di = *(int far *)&Dx8[NodeCnt + 0x2462] & 0xff;
        val1 = Dx8[NodeCnt + 0x246e];
        val2 = Dx8[NodeCnt + 0x247a];
        break;
    case 8:
        di = *(int far *)&Dx8[NodeCnt + 0x2486] & 0xff;
        val1 = Dx8[NodeCnt + 0x248c];
        val2 = Dx8[NodeCnt + 0x2492];
        break;
    case 9:
        di = *(int far *)&Dx8[NodeCnt + 0x2498] & 0xff;
        val1 = Dx8[NodeCnt + 0x249e];
        val2 = Dx8[NodeCnt + 0x24a4];
        break;
    case 10:
        di = *(int far *)&Dx8[NodeCnt + 0x24aa] & 0xff;
        val1 = Dx8[NodeCnt + 0x24ae];
        val2 = Dx8[NodeCnt + 0x24b2];
        break;
    case 11:
        di = *(int far *)&Dx8[NodeCnt + 0x24b6] & 0xff;
        val1 = Dx8[NodeCnt + 0x24ba];
        val2 = Dx8[NodeCnt + 0x24be];
        break;
    case 12:
        di = *(int far *)&Dx8[NodeCnt + 0x24c2] & 0xff;
        val1 = Dx8[NodeCnt + 0x24c8];
        val2 = Dx8[NodeCnt + 0x24ce];
        break;
    case 13:
        di = *(int far *)&Dx8[NodeCnt + 0x24d4] & 0xff;
        val1 = Dx8[NodeCnt + 0x24da];
        val2 = Dx8[NodeCnt + 0x24e0];
        break;
    case 14:
        di = *(int far *)&Dx8[NodeCnt + 0x24e6] & 0xff;
        val1 = Dx8[NodeCnt + 0x24ea];
        val2 = Dx8[NodeCnt + 0x24ee];
        break;
    case 15:
        di = *(int far *)&Dx8[NodeCnt + 0x24f2] & 0xff;
        val1 = Dx8[NodeCnt + 0x24f6];
        val2 = Dx8[NodeCnt + 0x24fa];
        break;
    case 20:
        di = *(int far *)&Dx8[NodeCnt * 2 + 0x24fe];
        val1 = Dx8[NodeCnt + 0x250e];
        val2 = Dx8[NodeCnt + 0x2516];
        goto skip_boy_store;
    case 21:
        di = *(int far *)&Dx8[NodeCnt * 2 + 0x251e];
        val1 = Dx8[NodeCnt + 0x2528];
        val2 = Dx8[NodeCnt + 0x252e];
        goto skip_boy_store;
    default:
        break;
    }

    BoyX = val1;
    BoyY = val2;

skip_boy_store:
    BoyFrame = di;

continue_common:
    BoyHere = 0;
    if (*statePtr == 0x26) {
        BoyDir = 1;
        BoyHere = 1;
    }
    if (*statePtr == 0x14 && NodeCnt > 2)
        BoyHere = 1;
    if (*statePtr == 0x15 && NodeCnt < 3)
        BoyHere = 1;
    BoyX = val1;
    BoyY = val2;
    BoyFrame = di;

    if (MapMode != 0 || YardMode >= 2)
        return;

    {
        int prevState = NodeCnt;
        int bx;
        if ((prevState == 3 && *statePtr == 0x14 && di == 0x384) ||
            (prevState == 1 && *statePtr == 0x15 && di == 0x387)) {
            myBeginSound(0x18, 0, 0);
        }

        {
            int px = BoyY + BoyX - 0xc8;
            int pcell = px / 0x1c;
            BoyPx = pcell;
        }
        FootHere = 0;
        FootTog = (*(int far *)&Dx8[0x8a82] < 1) ? 1 : 0;

        bx = CurYardPnt[0];
        bx = (bx << 4) + CurYardPnt[1];

        {
            int py = BoyY - 0x26;
            int pcell = py / 0xa;
            BoyPy = pcell;
            if (pcell != CurYardPnt[1])
                return;
        }
        if (BoyPx != CurYardPnt[0])
            return;

        if (bx == 0)
            return;
        if (bx == 1)
            return;
        if (bx == 0x10)
            return;
        if (bx == 0x20)
            return;

        if (BoyFrame >= 0 && BoyFrame < 0xc) {
            BoyDir = AlistT[BoyFrame];
        } else {
            BoyDir = 2;
        }
        FootHere = 1;

        {
            int py = (BoyY - 0x26) % 0xa;
            int px = (BoyY + BoyX - 0xc8) % 0x1c;
            int a = ((px + 1) * 3) << 2;
            a &= 0x3f;
            if ((BoyDir & 1) != 0) {
                if (FootTog != 0)
                    match_position[0x7a58 / 2] += 6;
                else
                    match_position[0x7a58 / 2] -= 6;
            } else {
                if (FootTog != 0)
                    match_position[0x7a4e / 2] -= 6;
            }
            FootFall(match_position[0x7a58 / 2], match_position[0x7a4e / 2]);
            myBeginSound(9, 0, 0x7e);
        }
    }

    {
        int total = (RpopT + BpopT) << 3;
        int tries = 0;
        if (total <= 0)
            goto colony_check;
        do {
            int cx, cy, idx, bx;
            cx = SRand128();
            cy = SRand64();
            bx = (cx << 6) + cy + 0x68e8;
            if (match_position[bx / 2] != 0) {
                idx = FindInAList(cy, cx);
                if (idx < 0)
                    continue;
                {
                    int flag = AlistT[match_position[idx / 2] & 0xff] & 0x80;
                    DeadAntHere(cy, cx, flag);
                }
                AlistT[match_position[idx / 2] & 0xff] = 0;
                match_position[bx / 2] = 0;
            }
            if ((SpidX >> 4) == cx && (SpidY >> 4) == cy)
                KillSpider();
            tries++;
        } while (tries <= total);
    }

colony_check:
    if (CurGameType == 2 && MePlane == 1) {
        if (SRand4(0) == 0)
            YellowDeath(9);
    }
}
