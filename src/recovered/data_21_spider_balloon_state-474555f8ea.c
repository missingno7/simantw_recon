/* Spider-balloon timing and message selection state start inactive. */
int __based(__segname("SIMANT_DATA_GROUP")) SpidBalloonTicks[2] = { 0, 0 };
int __based(__segname("SIMANT_DATA_GROUP")) SpidMsgOffset = -1;
