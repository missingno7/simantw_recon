/*
 * Unit review: PACK words reached as match_position[K] are the public
 * symbols match_position[0x3c36] -> TemBModePop[1], match_position[0x3c37] -> TemBModePop[2], match_position[0x3c38] -> TemBModePop[3], match_position[0x3c39] -> TemBModePop[4], match_position[0x3c3a] -> TemBModePop[5], match_position[0x3c3b] -> TemBModePop[6], match_position[0x3c3c] -> TemBModePop[7], match_position[0x3c41] -> TemBModePop[12], match_position[0x3df3] -> TemRModePop[1], match_position[0x3df4] -> TemRModePop[2], match_position[0x3df5] -> TemRModePop[3], match_position[0x3df6] -> TemRModePop[4], match_position[0x3df7] -> TemRModePop[5], match_position[0x3df8] -> TemRModePop[6], match_position[0x3df9] -> TemRModePop[7], match_position[0x3dfe] -> TemRModePop[12], match_position[0x3e05] -> TemRModePop[19] (one selector word per symbol in the object).
 *
 * TallyModePop: roll the per-submode ant counts (an unnamed far int
 * table in segment9, addressed here through the generic match_position[]
 * catch-all as in NotMowed/AddAntToBList/CompactListB) into the six
 * published ModePopB[]/ModePopR[] aggregate slots -- most pairs of
 * adjacent submode counts are summed, a few are copied singly.  If the
 * word at TemRModePop[19] is below 1, MakeRedInitiator() (a
 * same-code-group, LINK-translated near call) is invoked before
 * returning; otherwise the call just returns.
 */
extern int far match_position[];
extern int far TemBModePop[];
extern int far TemRModePop[];
extern int far ModePopB[];
extern int far ModePopR[];
extern void far MakeRedInitiator(void);

void near TallyModePop(void)
{
    ModePopB[0] = TemBModePop[2] + TemBModePop[3];
    ModePopB[1] = TemBModePop[4] + TemBModePop[5];
    ModePopB[2] = TemBModePop[1];
    ModePopB[3] = TemBModePop[7];
    ModePopB[4] = TemBModePop[12];
    ModePopB[5] = TemBModePop[6];

    ModePopR[0] = TemRModePop[2] + TemRModePop[3];
    ModePopR[1] = TemRModePop[4] + TemRModePop[5];
    ModePopR[2] = TemRModePop[1];
    ModePopR[3] = TemRModePop[7];
    ModePopR[4] = TemRModePop[12];
    ModePopR[5] = TemRModePop[6];

    if (TemRModePop[19] < 1)
        MakeRedInitiator();
}
