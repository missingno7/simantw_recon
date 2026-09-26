extern int far yardBalloonHandle; extern int far yardBalloon; extern void far Probe(void);
void far DrawSimKid(void){ int far *handle=&yardBalloonHandle; int far *balloon=&yardBalloon; if(*handle!=-1){ Probe(); *handle=-1; } if(*balloon!=0){ Probe(); *balloon=0; } }
