extern int far yardBalloonHandle; extern int far yardBalloon; extern void far Probe(void);
void far DrawSimKid(void){ int far * volatile handle=&yardBalloonHandle; int far * volatile balloon=&yardBalloon; if(*handle!=-1){ Probe(); *handle=-1; } if(*balloon!=0){ Probe(); *balloon=0; } }
