/* Report the immediate NetBIOS return byte and use the return-message table
   for status values outside the command-pending range. */
extern void far DebugWinPrintf(char far *format, ...);
extern char __based(__segname("SIMANT_DATA_GROUP")) NB_RETCODE[128][60];

void far NbImmediateStatus(unsigned char far *ncb)
{
    unsigned char status;

    status = ncb[1];
    if (status < 0x50)
        DebugWinPrintf("NetBIOS immediate status %u: %s", status,
                       NB_RETCODE[status]);
    else if (status < 0xf0)
        DebugWinPrintf("NetBIOS immediate status %u", status);
    else
        DebugWinPrintf("NetBIOS immediate status %u: %s", status,
                       NB_RETCODE[status]);
}
