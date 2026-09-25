/*
 * GetNewMode: choose an ant's next behaviour mode.  With the 0x80 flag
 * the caller is on the red side: mode 2 draws a new mode from
 * ModeTabWB[StrategicModeR][SRand8()], mode 6 from
 * ModeTabSB[StrategicModeR][SRand8()], any other mode maps through
 * CasteModeTabB[mode].  Without the flag, an automatic colony
 * (ModeAuto == 1) makes the same three-way choice with StrategicModeB;
 * a player-controlled colony keeps modes 2 and 6 at the player's
 * ModeMe and maps the rest through CasteModeTabB.  The result is kept
 * in one local newMode returned at the end (the target keeps it in SI:
 * cwde / mov si,ax / mov ax,si on the table paths, mov si,ModeMe on the
 * player path).
 *
 * Profile evidence (agentX): the shared 'shl bx,3 / add bx,ax / mov es /
 * mov al' lookup tails and the shared return tail are /Og cross-jumps;
 * under the og profile assigned to simtwo:0000 this nested if/else-if
 * form reproduces the size (192 bytes), the cross-jumped WB tail, the
 * mov di,si entry into the CasteModeTabB tail and the ModeMe epilogue.
 * Remaining: the flags branch reads mode into SI instead of DI, and the
 * compiler keeps the first copies of the SB and return tails (the
 * target keeps the later ones).
 */
extern int far SRand8(void);
extern char far ModeTabWB[][8];
extern char far ModeTabSB[][8];
extern char far CasteModeTabB[];
extern int far StrategicModeR;
extern int far StrategicModeB;
extern int far ModeAuto;
extern int far ModeMe;

int far GetNewMode(int mode, int flags)
{
    int newMode;

    if (flags & 0x80) {
        if (mode == 2)
            newMode = ModeTabWB[StrategicModeR][SRand8()];
        else if (mode == 6)
            newMode = ModeTabSB[StrategicModeR][SRand8()];
        else
            newMode = CasteModeTabB[mode];
    } else if (ModeAuto == 1) {
        if (mode == 2)
            newMode = ModeTabWB[StrategicModeB][SRand8()];
        else if (mode == 6)
            newMode = ModeTabSB[StrategicModeB][SRand8()];
        else
            newMode = CasteModeTabB[mode];
    } else {
        if (mode == 2 || mode == 6)
            newMode = ModeMe;
        else
            newMode = CasteModeTabB[mode];
    }
    return newMode;
}
