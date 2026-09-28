/* small compiler mechanism probe */
extern void far ProbeSink(int);
extern int far SMode,MeSMode,MeMode; extern int far SRand1(int); extern char far PyT[],PxT[],PyT2[],PxT2[],PyD[],PxD[],PyD2[],PxD2[]; void far DrawPalps(int x,int y,int direction){int sample=0; if(MeSMode<6 && SMode<=1) goto done; sample=SRand1(4); done: x+=PxT[sample]+PxT2[sample]; y+=PyT[sample]+PyT2[sample]+PxD[sample]+PxD2[sample];  ProbeSink(x+y+direction); }
