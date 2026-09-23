extern void far Punt(char far *message, ...);
void far Alpha(void) { Punt("Attempt to get obj address outsize window"); }
void far Beta(void) { Punt("Attempt to get obj address outsize window"); }
