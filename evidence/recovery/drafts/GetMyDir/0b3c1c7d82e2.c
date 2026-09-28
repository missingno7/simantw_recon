/* GetMyDir: select a best or randomized heading toward the requested plane. */
extern int far MeCrazyCnt;
extern int far MeCrazyDir;
extern int far MeCrazyRot;
extern int far LastNewHoleB[2];
extern int far LastNewHoleR[2];
extern int far LastNewExitB[2];
extern int far LastNewExitR[2];

extern int far CheckMyBestDirs(int far *steps, int plane, int x, int y,
                               int goalX, int goalY);
extern int far GetMyBestDirs(int plane, int x, int y, int goalX, int goalY);
extern int far GetMyRandDirs(int far *rotation, int far *direction,
                             int plane, int x, int y, int goalX, int goalY);
extern int far GetDir(int x, int y, int goalX, int goalY);

int far GetMyDir(int plane, int x, int y,
                 int goalPlane, int goalX, int goalY)
{
    int far *counter;
    int directSteps;
    int landmarkSteps;
    int targetX;
    int targetY;
    int answer;
    int check;

    /* Surface destinations need no remembered landmark.  A request from an
     * underground plane for that same plane also uses its literal goal. */
    if (plane <= 1) {
        if (goalPlane <= 1) {
            counter = &MeCrazyCnt;
            if (*counter < 0)
                goto direct_calm;
            check = CheckMyBestDirs(&directSteps, plane, x, y,
                                    goalX, goalY);
            if (check == -2)
                goto direct_shuffle;
            goto direct_best;
        }

        if (goalPlane == 2) {
            targetX = LastNewHoleB[0];
            targetY = LastNewHoleB[1];
        } else {
            targetX = LastNewHoleR[0];
            targetY = LastNewHoleR[1];
        }
        counter = &MeCrazyCnt;
        if (*counter < 0)
            goto landmark_calm;
        goto landmark_armed;
    }

    if (goalPlane == plane) {
        counter = &MeCrazyCnt;
        if (*counter < 0)
            goto direct_calm;
        check = CheckMyBestDirs(&directSteps, plane, x, y,
                                goalX, goalY);
        if (check == -2)
            goto direct_shuffle;
        goto direct_best;
    }

    if (plane == 2) {
        targetX = LastNewExitB[0];
        targetY = LastNewExitB[1];
        counter = &MeCrazyCnt;
        if (*counter < 0)
            goto landmark_calm;
        goto landmark_armed;
    }
    targetX = LastNewExitR[0];
    targetY = LastNewExitR[1];
    counter = &MeCrazyCnt;
    if (*counter < 0)
        goto landmark_calm;

    check = CheckMyBestDirs(&landmarkSteps, plane, x, y, targetX, targetY);
    goto landmark_result;

landmark_armed:
    check = CheckMyBestDirs(&landmarkSteps, plane, x, y, targetX, targetY);
landmark_result:
    if (check == -2) {
        answer = GetMyRandDirs(&MeCrazyRot, &MeCrazyDir, plane, x, y,
                               targetX, targetY);
    } else {
        *counter = -1;
        answer = GetMyBestDirs(plane, x, y, targetX, targetY);
    }
    --*counter;
    return answer;

landmark_calm:
    answer = GetMyBestDirs(plane, x, y, targetX, targetY);
    if (answer == -2 && *counter == answer) {
        MeCrazyDir = GetDir(x, y, targetX, targetY) - 1;
        *counter = 0x10;
        MeCrazyRot = 0;
        answer = GetMyRandDirs(&MeCrazyRot, &MeCrazyDir, plane, x, y,
                               targetX, targetY);
    }
    return answer;

direct_best:
    *counter = -1;
    answer = GetMyBestDirs(plane, x, y, goalX, goalY);
    --*counter;
    return answer;

direct_shuffle:
    answer = GetMyRandDirs(&MeCrazyRot, &MeCrazyDir, plane, x, y,
                           goalX, goalY);
    --*counter;
    return answer;

direct_calm:
    answer = GetMyBestDirs(plane, x, y, goalX, goalY);
    if (answer == -2 && *counter == answer) {
        MeCrazyDir = GetDir(x, y, goalX, goalY) - 1;
        *counter = 0x10;
        MeCrazyRot = 0;
        answer = GetMyRandDirs(&MeCrazyRot, &MeCrazyDir, plane, x, y,
                               goalX, goalY);
    }
    return answer;
}
