extern unsigned char __based(__segname("SIMANT_DATA_GROUP")) AlistX[];
extern unsigned char __based(__segname("SIMANT_DATA_GROUP")) AlistY[];
extern unsigned char __based(__segname("SIMANT_DATA_GROUP")) Dx8[];
extern unsigned char near LifeA[];
extern int __based(__segname("PACK")) ListIndexA;
extern void far BlockMove(unsigned char far *source, unsigned char far *destination, long count);
void far RemoveFromAList(int index) {
    long count;
    LifeA[(AlistX[index] << 6) + AlistY[index]] = 0;
    if (ListIndexA <= 0) return;
    --ListIndexA;
    count = ListIndexA - index;
    BlockMove(&AlistX[index + 1], &AlistX[index], count);
    BlockMove(&AlistY[index + 1], &AlistY[index], count);
    BlockMove(&Dx8[index + 1 + 0x2b78], &Dx8[index + 0x2b78], count);
    BlockMove(&Dx8[index + 1 + 0x2f62], &Dx8[index + 0x2f62], count);
    BlockMove(&Dx8[index + 1 + 0x334c], &Dx8[index + 0x334c], count);
}
