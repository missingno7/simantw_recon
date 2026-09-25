/* Yard UI handles begin empty; unopened native handles use the -1 sentinel.
 * The text/name records later in yardMsgHandle's public span are private data.
 */
int __based(__segname("SIMANT_DATA_GROUP")) yardBalloon = 0;
int __based(__segname("SIMANT_DATA_GROUP")) yardMsgBuf = 0;
int __based(__segname("SIMANT_DATA_GROUP")) yardBalloonHandle = -1;
int __based(__segname("SIMANT_DATA_GROUP")) yardMsgHandle = -1;
