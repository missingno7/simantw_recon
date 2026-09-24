/* Selector-typed control: test C7's near __segment formal with the same actual. */
extern int far GetMyRandDirs(int far *rotation, int near *direction,
                              __segment near selector, int a2, int a3, int a4, int a5);
void far ProbeFormal(void)
{
    GetMyRandDirs((int far *)0, (int near *)0, __segname("PACK"), 1, 2, 3, 4);
}