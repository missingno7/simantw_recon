struct ButtonHeldState {
    unsigned long tick;
    unsigned int count;
    unsigned int active;
};

extern struct ButtonHeldState far Scycle[];
extern unsigned long far TickCount(void);

void ButtonHeldInit(void)
{
    Scycle[-12].tick = TickCount();
    Scycle[-12].active = 2;
    Scycle[-12].count = 0;
}
