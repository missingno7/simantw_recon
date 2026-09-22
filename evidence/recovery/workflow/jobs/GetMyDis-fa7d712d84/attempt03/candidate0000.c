/*
 * GetMyDis: combined distance between two indexed reference points and the
 * two supplied ant positions.  i1/i2 select among four fixed yard
 * landmarks (1=B exit, 2=B hole, otherwise R exit/R hole by branch), each
 * a 2-word (x,y) far pair.  Equal indices collapse to a plain distance
 * between the two supplied positions.  Otherwise the result sums a
 * distance from (x2,y2) to the landmark matching i1 (or i2's landmark
 * when i1 does not resolve one directly) with a distance from (x1,y1) to
 * the complementary landmark; the remaining index combinations (neither
 * index matching 1, or i1 matching 2 while i2 does not match 1) instead
 * sum three legs, adding the fixed BHole-to-RHole distance as a middle
 * term.
 */
extern int far LastNewExitB[2];
extern int far LastNewHoleB[2];
extern int far LastNewExitR[2];
extern int far LastNewHoleR[2];

extern int far GetDis(int x1, int y1, int x2, int y2);

int far GetMyDis(int i1, int x1, int y1, int i2, int x2, int y2)
{
    int sum;

    if (i1 == i2)
        return GetDis(x1, y1, x2, y2);

    if (i1 != 1)
        goto check_i2;
    if (i2 <= 1)
        goto check_i2;

    if (i2 != 2)
        goto i1_1_i2_3;
    sum = GetDis(LastNewExitB[0], LastNewExitB[1], x2, y2);
    return sum + GetDis(x1, y1, LastNewHoleB[0], LastNewHoleB[1]);

i1_1_i2_3:
    sum = GetDis(LastNewExitB[0], LastNewExitB[1], x2, y2);
    return sum + GetDis(x1, y1, LastNewHoleR[0], LastNewHoleR[1]);

check_i2:
    if (i2 != 1)
        goto check_i1_2;

    if (i1 != 2)
        goto i2_1_i1_other;
    sum = GetDis(LastNewHoleB[0], LastNewHoleB[1], x2, y2);
    return sum + GetDis(x1, y1, LastNewExitB[0], LastNewExitB[1]);

i2_1_i1_other:
    sum = GetDis(LastNewHoleR[0], LastNewHoleR[1], x2, y2);
    return sum + GetDis(x1, y1, LastNewExitR[0], LastNewExitR[1]);

check_i1_2:
    if (i1 != 2)
        goto default_case;

    sum = GetDis(LastNewExitR[0], LastNewExitR[1], x2, y2);
    sum += GetDis(LastNewHoleB[0], LastNewHoleB[1], LastNewHoleR[0], LastNewHoleR[1]);
    return sum + GetDis(x1, y1, LastNewExitB[0], LastNewExitB[1]);

default_case:
    sum = GetDis(LastNewExitB[0], LastNewExitB[1], x2, y2);
    sum += GetDis(LastNewHoleB[0], LastNewHoleB[1], LastNewHoleR[0], LastNewHoleR[1]);
    return sum + GetDis(x1, y1, LastNewExitR[0], LastNewExitR[1]);
}
