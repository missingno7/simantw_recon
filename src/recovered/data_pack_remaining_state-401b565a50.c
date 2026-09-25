/*
 * Final small PACK map, resource and colony fields.  GrassMap is a 12-word
 * terrain table, initialization and window-title links are far pointers, and
 * the remaining counters are zero-initialized 16- or 32-bit values.
 */
int __based(__segname("PACK")) miniJust = 0;
char far * __based(__segname("PACK")) iniPath = 0;
int __based(__segname("PACK")) GrassMap[12] = {0};
int __based(__segname("PACK")) CurEggPlane = 0;
int __based(__segname("PACK")) gSlowMac = 0;
int __based(__segname("PACK")) lastSubState = 0;
int __based(__segname("PACK")) WantRFightBalloon = 0;
int __based(__segname("PACK")) MeLastX = 0;
int __based(__segname("PACK")) MeCrazyDir = 0;
int __based(__segname("PACK")) MeLastY = 0;
int __based(__segname("PACK")) BColoniesKilled = 0;
int __based(__segname("PACK")) mapMapBuf = 0;
char far * __based(__segname("PACK")) MapWinTitles = 0;
int __based(__segname("PACK")) RedLost = 0;
long __based(__segname("PACK")) EggBalloonTicks = 0L;
int __based(__segname("PACK")) win_numOfColors = 0;
char far * __based(__segname("PACK")) RFightMsgs = 0;
