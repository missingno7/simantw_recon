/*
 * LoadFancyCursor: load the seven custom cursors from the application's
 * resources.  Each call is the USER ordinal-173 Pascal import LoadCursor
 * (instance handle, far resource name); the names are the private DGROUP
 * string literals "MagCursor", "RockCursor", "DigCursor", "AntCursor",
 * "FoodCursor", "DropCursor" and "SprayCursor" (fixture bytes 0x32a..0x373,
 * emitted in call order), and each handle is stored in its MAPSYM-named
 * near DGROUP word.  hInst is the near instance handle used elsewhere.
 */
extern unsigned int far pascal LoadCursor(unsigned int instance,
                                          char far *name);
extern int near hInst;
extern unsigned int near magCursor;
extern unsigned int near rockCursor;
extern unsigned int near digCursor;
extern unsigned int near antCursor;
extern unsigned int near foodCursor;
extern unsigned int near dropCursor;
extern unsigned int near sprayCursor;

void far LoadFancyCursor(void)
{
    magCursor = LoadCursor(hInst, "MagCursor");
    rockCursor = LoadCursor(hInst, "RockCursor");
    digCursor = LoadCursor(hInst, "DigCursor");
    antCursor = LoadCursor(hInst, "AntCursor");
    foodCursor = LoadCursor(hInst, "FoodCursor");
    dropCursor = LoadCursor(hInst, "DropCursor");
    sprayCursor = LoadCursor(hInst, "SprayCursor");
}
