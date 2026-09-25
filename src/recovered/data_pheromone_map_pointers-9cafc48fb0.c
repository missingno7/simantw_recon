/* Near globals that retain the active far pheromone planes for black and red colonies. */
extern unsigned char far PherMapA[];
extern unsigned char far PherMapBN[];
extern unsigned char far PherMapBT[];
extern unsigned char far PherMapRN[];
extern unsigned char far PherMapRT[];

unsigned char far * near PherMapAPtr = PherMapA;
unsigned char far * near PherMapBNPtr = PherMapBN;
unsigned char far * near PherMapBTPtr = PherMapBT;
unsigned char far * near PherMapRNPtr = PherMapRN;
