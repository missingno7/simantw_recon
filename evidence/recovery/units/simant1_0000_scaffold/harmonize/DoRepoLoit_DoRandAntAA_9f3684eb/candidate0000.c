/*
 * DoRepoLoit: a repopulation ant loitering in the generic A list.  Half the
 * time (SRand2) it wanders (DoRandAntAA), otherwise it heads for the nest
 * (DoToNestAnt).  Then, if the colony it belongs to (AlistT bit 0x80: red)
 * has more than 100 ants flying away (FlyAwayR / FlyAwayB), the current
 * list record (Tindex) is switched to mode 0xf.  The A-list fields are the
 * public based arrays of SIMANT_DATA_GROUP; the compiler loads that segment
 * and PACK immediately (no pool words) and restores DS from SS at the end.
 * The two colony branches share their `> 100` tail.
 */
extern int far SRand2(void);
extern void far DoRandAntAA(int index);
extern void near DoToNestAnt(int index);
extern unsigned char __based(__segname("SIMANT_DATA_GROUP")) AlistT[];
extern unsigned char __based(__segname("SIMANT_DATA_GROUP")) AlistM[];
extern int far FlyAwayR;
extern int far FlyAwayB;
extern int far Tindex;

void near DoRepoLoit(int index)
{
    if (SRand2())
        DoRandAntAA(index);
    else
        DoToNestAnt(index);

    if (AlistT[index] & 0x80) {
        if (FlyAwayR > 100)
            AlistM[Tindex] = 0xf;
    } else {
        if (FlyAwayB > 100)
            AlistM[Tindex] = 0xf;
    }
}
