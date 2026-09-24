/* Synthetic-only C7 selector-allocation microfixture. */
extern int far FixturePrefix00[];
extern int far FixturePrefix01[];
extern int far FixturePrefix02[];
extern int far FixturePrefix03[];
extern int far FixturePrefix04[];
extern int far FixturePrefix05[];
extern int far FixturePrefix06[];
extern int far FixturePrefix07[];
extern int far FixturePrefix08[];
extern int far FixturePrefix09[];
extern int far FixturePrefix10[];
extern int far FixturePrefix11[];
extern int far FixturePrefix12[];
extern int far FixturePrefix13[];
extern int far FixturePrefix14[];
extern int far FixturePrefix15[];
extern int far FixturePrefix16[];
extern int far FixturePrefix17[];
extern int far FixturePrefix18[];
extern int far FixturePrefix19[];
extern int far FixturePrefix20[];
extern int far FixturePrefix21[];
extern int far FixturePrefix22[];
extern int far FixturePrefix23[];
extern int far FixturePrefix24[];
extern int far FixturePrefix25[];
extern int far FixturePrefix26[];
extern int far FixtureExit00[];
extern int far FixtureExit01[];
extern int far FixtureExit02[];
extern int far FixtureDis00[];
extern int far FixtureDis01[];
extern int far FixtureDis02[];
extern int far FixtureDis03[];
extern int far FixtureNext00[];
extern int far FixtureInitial00[];
extern int far FixtureInitial01[];
void far ProbePrefix(void) {
    volatile int sink;
    sink = FixturePrefix00[0];
    sink = FixturePrefix01[0];
    sink = FixturePrefix02[0];
    sink = FixturePrefix03[0];
    sink = FixturePrefix04[0];
    sink = FixturePrefix05[0];
    sink = FixturePrefix06[0];
    sink = FixturePrefix07[0];
    sink = FixturePrefix08[0];
    sink = FixturePrefix09[0];
    sink = FixturePrefix10[0];
    sink = FixturePrefix11[0];
    sink = FixturePrefix12[0];
    sink = FixturePrefix13[0];
    sink = FixturePrefix14[0];
    sink = FixturePrefix15[0];
    sink = FixturePrefix16[0];
    sink = FixturePrefix17[0];
    sink = FixturePrefix18[0];
    sink = FixturePrefix19[0];
    sink = FixturePrefix20[0];
    sink = FixturePrefix21[0];
    sink = FixturePrefix22[0];
    sink = FixturePrefix23[0];
    sink = FixturePrefix24[0];
    sink = FixturePrefix25[0];
    sink = FixturePrefix26[0];
}
void far ProbeExit(void) {
    volatile int sink;
    sink = FixtureExit00[0];
    sink = FixtureExit01[0];
    sink = FixtureExit02[0];
}
void far ProbeDis(void) {
    volatile int sink;
    sink = FixtureDis00[0];
    sink = FixtureDis01[0];
    sink = FixtureDis02[0];
    sink = FixtureDis03[0];
}
void far ProbeNext(void) {
    volatile int sink;
    sink = FixtureNext00[0];
}
void far ProbeInitial(void) {
    volatile int sink;
    sink = FixtureInitial00[0];
    sink = FixtureInitial01[0];
}
