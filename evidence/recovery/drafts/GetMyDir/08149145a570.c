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
extern int far GetMyRandDirs(int far *rotation, int near *direction, int selector, int plane, int x, int y, int goalX, int goalY);
extern int far GetDir(int x, int y, int goalX, int goalY);

int far GetMyDir(int plane, int x, int y,
                 int goalPlane, int goalX, int goalY)
{
    int far *counter;
    int landmarkSteps;
    int targetX;
    int directStepsOrTargetY;
    int answer;
    int check;

    /* Surface destinations need no remembered landmark.  A request from an
     * underground plane for that same plane also uses its literal goal. */
    if (plane <= 1) {
        if (goalPlane <= 1) {
            counter = &MeCrazyCnt;
            if (*counter < 0) {
                answer = GetMyBestDirs(plane, x, y, goalX, goalY);
                if (answer == -2 && *counter == answer) {
                    MeCrazyDir = GetDir(x, y, goalX, goalY) - 1;
                    *counter = 0x10;
                    MeCrazyRot = 0;
                    answer = GetMyRandDirs(&MeCrazyRot, (int near *)&MeCrazyDir,
                                           __segname("PACK"), plane, x, y,
                                           goalX, goalY);
                }
                return answer;
            }
            check = CheckMyBestDirs(&directStepsOrTargetY, plane, x, y,
                                    goalX, goalY);
            if (check == -2) {
                answer = GetMyRandDirs(&MeCrazyRot, (int near *)&MeCrazyDir,
                                       __segname("PACK"), plane, x, y,
                                       goalX, goalY);
                --*counter;
                return answer;
            }
            *counter = -1;
            answer = GetMyBestDirs(plane, x, y, goalX, goalY);
            --*counter;
            return answer;
        }

        if (goalPlane == 2) {
            targetX = LastNewHoleB[0];
            directStepsOrTargetY = LastNewHoleB[1];
        } else {
            targetX = LastNewHoleR[0];
            directStepsOrTargetY = LastNewHoleR[1];
        }
        counter = &MeCrazyCnt;
        if (*counter < 0)
            goto landmark_calm;
        goto landmark_armed;
    }

    if (goalPlane == plane) {
        counter = &MeCrazyCnt;
        if (*counter < 0) {
            answer = GetMyBestDirs(plane, x, y, goalX, goalY);
            if (answer == -2 && *counter == answer) {
                MeCrazyDir = GetDir(x, y, goalX, goalY) - 1;
                *counter = 0x10;
                MeCrazyRot = 0;
                answer = GetMyRandDirs(&MeCrazyRot, (int near *)&MeCrazyDir,
                                       __segname("PACK"), plane, x, y,
                                       goalX, goalY);
            }
            return answer;
        }
        check = CheckMyBestDirs(&directStepsOrTargetY, plane, x, y,
                                goalX, goalY);
        if (check == -2) {
            answer = GetMyRandDirs(&MeCrazyRot, (int near *)&MeCrazyDir,
                                   __segname("PACK"), plane, x, y,
                                   goalX, goalY);
            --*counter;
            return answer;
        }
        *counter = -1;
        answer = GetMyBestDirs(plane, x, y, goalX, goalY);
        --*counter;
        return answer;
    }

    if (plane == 2) {
        targetX = LastNewExitB[0];
        directStepsOrTargetY = LastNewExitB[1];
        counter = &MeCrazyCnt;
        if (*counter < 0)
            goto landmark_calm;
        goto landmark_armed;
    }
    targetX = LastNewExitR[0];
    directStepsOrTargetY = LastNewExitR[1];
    counter = &MeCrazyCnt;
    if (*counter < 0)
        goto landmark_calm;

    check = CheckMyBestDirs(&landmarkSteps, plane, x, y, targetX, directStepsOrTargetY);
    if (check == -2) {
        answer = GetMyRandDirs(&MeCrazyRot, (int near *)&MeCrazyDir,
                               __segname("PACK"), plane, x, y,
                               targetX, directStepsOrTargetY);
    } else {
        *counter = -1;
        answer = GetMyBestDirs(plane, x, y, targetX, directStepsOrTargetY);
    }
    --*counter;
    return answer;

landmark_armed:
    check = CheckMyBestDirs(&landmarkSteps, plane, x, y, targetX, directStepsOrTargetY);
    if (check == -2) {
        answer = GetMyRandDirs(&MeCrazyRot, (int near *)&MeCrazyDir, __segname("PACK"), plane, x, y,
                               targetX, directStepsOrTargetY);
    } else {
        *counter = -1;
        answer = GetMyBestDirs(plane, x, y, targetX, directStepsOrTargetY);
    }
    --*counter;
    return answer;

landmark_calm:
    answer = GetMyBestDirs(plane, x, y, targetX, directStepsOrTargetY);
    if (answer == -2 && *counter == answer) {
        MeCrazyDir = GetDir(x, y, targetX, directStepsOrTargetY) - 1;
        *counter = 0x10;
        MeCrazyRot = 0;
        answer = GetMyRandDirs(&MeCrazyRot, (int near *)&MeCrazyDir, __segname("PACK"), plane, x, y,
                               targetX, directStepsOrTargetY);
    }
    return answer;

}


