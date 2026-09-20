extern int far GameSpeed;
extern int far MeWarnHealth;
extern int far BlkWarnHealth;
extern int far CurExpTool;
extern int far SwarmCntR;
extern int far SwarmCntB;
extern int near QueenStorageR;
extern int near QueenStorageB;

void InitSimVars(void)
{
    GameSpeed = 1;
    MeWarnHealth = 30;
    BlkWarnHealth = 30;
    CurExpTool = 0;
    SwarmCntR = 0;
    SwarmCntB = 0;
    QueenStorageR = 0;
    QueenStorageB = 0;
}
