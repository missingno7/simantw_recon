extern int far LionIndex; extern void far Probe(void);
void far InitAntLions(void){ int far *pli; pli=&LionIndex; *pli=0; Probe(); *pli=*pli+1; Probe(); *pli=*pli+1; }
