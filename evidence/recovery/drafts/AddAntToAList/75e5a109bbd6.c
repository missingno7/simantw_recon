extern int far ListIndexA;
extern unsigned char __based(__segname("SIMANT_DATA_GROUP")) AlistX[];
extern unsigned char __based(__segname("SIMANT_DATA_GROUP")) AlistY[];
extern unsigned char __based(__segname("SIMANT_DATA_GROUP")) AlistM[];
extern unsigned char __based(__segname("SIMANT_DATA_GROUP")) AlistT[];
extern unsigned char __based(__segname("SIMANT_DATA_GROUP")) AlistS[];
extern unsigned char near LifeA[128][64];
void far AddAntToAList(int life, int column, int state, int attribute, int direction)
{
    register int count;
    if (ListIndexA >= 1000)
        return;
    count = ListIndexA;
    AlistX[count] = (unsigned char)life;
    AlistY[count] = (unsigned char)column;
    AlistM[count] = (unsigned char)attribute;
    AlistT[count] = (unsigned char)state;
    AlistS[count] = (unsigned char)direction;
    LifeA[life][column] = (unsigned char)state;
    ListIndexA = ListIndexA + 1;
}
