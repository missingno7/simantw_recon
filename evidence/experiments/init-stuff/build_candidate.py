from pathlib import Path

root = Path(__file__).resolve().parent
source = (root.parent / "prepare-strings" / "first.c").read_text()
source = source.replace("void far PrepareStrings(void)", "void far initStuff(void)")
source = source.replace(
    "/* Load the text tables in their observed resource order. */",
    "/* Load the startup strings, database table, and simulation state. */",
)
source = source.replace(
    "void far initStuff(void)\n{",
    """extern unsigned int far db_LoadObject(int object, int kind, int lock);
extern void far WinPrintf(char far *format, ...);
extern void far Quit(char far *message, int code);
extern void far FlipHandleWords(unsigned int handle);
extern void far *mem_Lock(unsigned int handle);
extern int far mem_Unlock(unsigned int handle);
extern char far * far * far FracSineTab;
extern void far initSimWindows(void);
extern void far OverlayOutsideTiles(void);
extern int far BootUpGame(void);
extern void far InitSimVars(void);
extern void far SeedSRand(void);
extern void far SeedRRand(void);
extern void far SetSimCursor(int cursor);

void far initStuff(void)
{
    unsigned int handle;
    int resourceError;""",
)
last = source.rfind("\n}")
assert last >= 0
source = source[:last] + """
    handle = db_LoadObject(1000, 9, 0);
    if (handle == 0) {
        WinPrintf("Cannot GetResource (HEX, %d), ResErr %d\\n", 1000,
                  resourceError);
        Quit("MemDeath", handle);
    }
    FlipHandleWords(handle);
    FracSineTab = (char far * far *)mem_Lock(handle);
    mem_Unlock(handle);
    initSimWindows();
    OverlayOutsideTiles();
    if (BootUpGame() == 0) {
        InitSimVars();
        SeedSRand();
        SeedRRand();
    }
    SetSimCursor(0);
}
"""
(root / "first.c").write_text(source)
