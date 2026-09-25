/* Load the text tables in their observed resource order. */
extern char far * far * far LoadStringAnt(int object);
extern char far * far * far MwinTitle;
extern char far * far * far ScenarioNameStrs;
extern char far * far * far WindPromptStrs;
extern char far * far * far AdviceStrs;
extern char far * far * far HistGraphStrs;
extern char far * far * far EggStr;
extern char far * far * far CasteStr;
extern char far * far * far ModeStr;
extern char far * far * far LoadStr;
extern char far * far * far BoyMsgs;
extern char far * far * far SpiderMsgs;
extern char far * far * far BFightMsgs;
extern char far * far * far RFightMsgs;
extern char far * far * far EggMsgs;
extern char far * far * far QueenMsgs;
extern char far * far * far RestMsgs;
extern char far * far * far EndGameRatingStrs;
extern char far * far * far MiscStrs;

void far PrepareStrings(void)
{
    MwinTitle = LoadStringAnt(1000);
    ScenarioNameStrs = LoadStringAnt(1001);
    WindPromptStrs = LoadStringAnt(1010);
    AdviceStrs = LoadStringAnt(1020);
    HistGraphStrs = LoadStringAnt(1050);
    EggStr = LoadStringAnt(1100);
    CasteStr = LoadStringAnt(1101);
    ModeStr = LoadStringAnt(1102);
    LoadStr = LoadStringAnt(1103);
    BoyMsgs = LoadStringAnt(1200);
    SpiderMsgs = LoadStringAnt(1210);
    BFightMsgs = LoadStringAnt(1220);
    RFightMsgs = LoadStringAnt(1230);
    EggMsgs = LoadStringAnt(1240);
    QueenMsgs = LoadStringAnt(1250);
    RestMsgs = LoadStringAnt(1260);
    EndGameRatingStrs = LoadStringAnt(1900);
    MiscStrs = LoadStringAnt(1800);
}
