/*
 * TallyModePop: roll the per-submode ant counts (an unnamed far int
 * table in segment9, addressed here through the generic match_position[]
 * catch-all as in NotMowed/AddAntToBList/CompactListB) into the six
 * published ModePopB[]/ModePopR[] aggregate slots -- most pairs of
 * adjacent submode counts are summed, a few are copied singly.  If the
 * word at match_position[0x3e05] is below 1, MakeRedInitiator() (a
 * same-code-group, LINK-translated near call) is invoked before
 * returning; otherwise the call just returns.
 */
extern int far match_position[];
extern int far ModePopB[];
extern int far ModePopR[];
extern void far MakeRedInitiator(void);

void near TallyModePop(void)
{
    ModePopB[0] = match_position[0x3c37] + match_position[0x3c38];
    ModePopB[1] = match_position[0x3c39] + match_position[0x3c3a];
    ModePopB[2] = match_position[0x3c36];
    ModePopB[3] = match_position[0x3c3c];
    ModePopB[4] = match_position[0x3c41];
    ModePopB[5] = match_position[0x3c3b];

    ModePopR[0] = match_position[0x3df4] + match_position[0x3df5];
    ModePopR[1] = match_position[0x3df6] + match_position[0x3df7];
    ModePopR[2] = match_position[0x3df3];
    ModePopR[3] = match_position[0x3df9];
    ModePopR[4] = match_position[0x3dfe];
    ModePopR[5] = match_position[0x3df8];

    if (match_position[0x3e05] < 1)
        MakeRedInitiator();
}
