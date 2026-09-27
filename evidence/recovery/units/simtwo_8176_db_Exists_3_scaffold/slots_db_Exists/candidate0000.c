extern int far sprintf(char far *buffer, char far *format, ...);
extern int far access(char far *path, int mode);

int db_Exists(char far *name)
{
    char path[100];

    sprintf(path, "%s.dat", name);
    if (access(path, 0) != -1)
        return 1;
    return 0;
}
