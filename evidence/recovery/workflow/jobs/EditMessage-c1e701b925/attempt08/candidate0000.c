extern int far OptionStates[];
extern long far editMessage;
extern long far editMessageRemoveTime;
extern long far mapMessage;
extern long far mapMessageRemoveTime;
extern unsigned long far TickCount(void);
extern int far win_IsWinOpen(int window);
extern void near DrawRibbonMessage(void);
extern void far DrawAnimYardMessage(void);

void far EditMessage(long message, long duration, int mode)
{
    if (mode == 0) {
        if (OptionStates[4] != 0 && editMessage == 0L)
            goto update_message;
        if (message != 0L || editMessageRemoveTime != 0x7fffffffL)
            return;
    }

update_message:
    if (duration >= 0L)
        editMessageRemoveTime = (duration * 3L) / 2L + TickCount();
    else
        editMessageRemoveTime = 0x7fffffffL;

    if (message != editMessage)
        editMessage = message;

    if (duration >= 0L)
        mapMessageRemoveTime = (duration * 3L) / 2L + TickCount();
    else
        mapMessageRemoveTime = 0x7fffffffL;

    if (message != mapMessage)
        mapMessage = message;

    if (win_IsWinOpen(0x2200))
        DrawRibbonMessage();
    if (win_IsWinOpen(0x1900))
        DrawAnimYardMessage();
}

