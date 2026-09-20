/*
 * Pre-load initialization clears the editor/runtime state in four far data
 * areas, seeds the yard-size word with 300, and then creates the randomized
 * yard contents.
 */
struct PreloadA {
    unsigned char pad[0x9c70];
    unsigned int flag;
};
struct PreloadB {
    unsigned char pad[0x806e];
    unsigned int at806e;
    unsigned int at8070;
};
struct PreloadC {
    unsigned char pad[0x9b10];
    unsigned int size;
    unsigned int used;
};
struct PreloadD {
    unsigned char pad[0x9e9e];
    unsigned int first;
    unsigned int second;
};
extern struct PreloadA far preloadStateA;
extern struct PreloadB far preloadStateB;
extern struct PreloadC far preloadStateC;
extern struct PreloadD far preloadStateD;
extern void far RandYard(void);

void DoPreLoadInits(void)
{
    preloadStateA.flag = 1;
    preloadStateB.at8070 = 0;
    preloadStateB.at806e = 0;
    preloadStateC.size = 0x12c;
    preloadStateC.used = 0;
    preloadStateD.second = 0;
    preloadStateD.first = 0;
    RandYard();
}
