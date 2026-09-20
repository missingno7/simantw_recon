/*
 * Pre-load initialization clears the editor/runtime state in four far data
 * areas, seeds the yard-size word with 300, and then creates the randomized
 * yard contents.
 */
extern unsigned int far preloadStateA[];
extern unsigned int far preloadStateB[];
extern unsigned int far preloadStateC[];
extern unsigned int far preloadStateD[];
extern void far RandYard(void);

void DoPreLoadInits(void)
{
    preloadStateA[0x9c70] = 1;
    preloadStateB[0x806e] = 0;
    preloadStateB[0x8070] = 0;
    preloadStateC[0x9b10] = 0x12c;
    preloadStateC[0x9b12] = 0;
    preloadStateD[0x9e9e] = 0;
    preloadStateD[0x9ea0] = 0;
    RandYard();
}
