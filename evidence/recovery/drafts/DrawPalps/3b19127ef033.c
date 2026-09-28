/* small compiler mechanism probe */
extern void far ProbeSink(int);
extern int far SMode,MeSMode,MeMode; extern int far SRand1(int); extern char far PyT[],PxT[],PyT2[],PxT2[],PyD[],PxD[],PyD2[],PxD2[]; void far DrawPalps(int x,int y,int direction){register int sample; if(SMode>1||MeSMode>=6) sample=SRand1(4); else sample=0; x+=PxT[sample]+PyT[sample]+PxT2[sample]+PyT2[sample]; x+=PxD[sample]+PyD[sample]+PxD2[sample]+PyD2[sample];  ProbeSink(x+y+direction); }
