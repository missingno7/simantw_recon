/* Dispatch table for the eight directional ant-step routines. */
extern int far goStepUp(int step);
extern int far goStepNE(int step);
extern int far goStepRight(int step);
extern int far goStepSE(int step);
extern int far goStepDown(int step);
extern int far goStepSW(int step);
extern int far goStepLeft(int step);
extern int far goStepNW(int step);
typedef int (far *StepRoutine)(int step);
StepRoutine near StepDirFuncArray[8] = { goStepUp, goStepNE, goStepRight, goStepSE, goStepDown, goStepSW, goStepLeft, goStepNW };
