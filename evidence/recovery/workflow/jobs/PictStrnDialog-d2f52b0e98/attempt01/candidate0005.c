/*
 * PictStrnDialog: show a picture dialog with a string table.  Unless
 * forced, the dialog only appears when option state 3 is set.  The
 * simulation is stopped, the string table object is loaded (a far array
 * of far strings ending in a null pointer) and its entries counted, the
 * picture dialog runs with the table, count, picture and force flag, the
 * table is freed, the string object purged from the database (kind 4)
 * and the simulation restarted.
 */
extern int far OptionStates[];

extern void far StopSimulation(void);
extern char far * far * far LoadStringAnt(int object);
extern void far PictureDialog(char far * far *strings, int count, int picture, int force);
extern void far free(void far *block);
extern void far db_PurgeObject(int object, int kind);
extern void far RestartSimulation(void);

void far PictStrnDialog(int picture, int object, int force)
{
    int count;
    char far * far *strings;
    char far * far *p;

    if (force != 0 || OptionStates[3] != 0) {
        StopSimulation();
        count = 0;
        strings = LoadStringAnt(object);
        if (strings) {
            for (p = strings; *p != 0; p++)
                count++;
        }
        PictureDialog(strings, count, picture, force);
        if (strings)
            free(strings);
        db_PurgeObject(object, 4);
        RestartSimulation();
    }
}
