/*
 * SeparateFile: split a far path into its directory and file name
 * parts.  Starting at the terminating NUL (lstrlen), the path is walked
 * back with AnsiPrev until a ':' or '\' separator or the start of the
 * string.  Without a separator the whole path is the file name and the
 * directory is emptied.  Otherwise the name is copied from just past the
 * separator, the whole path is copied into the directory buffer (the
 * first name character being saved and restored around the copy, a
 * leftover of an in-place cut) and the directory is terminated right
 * after the separator.  The first (word) parameter is unused.
 */
#define FP_OFF(fp) ((unsigned)(unsigned long)(fp))
extern int far pascal lstrlen(char far *string);
extern char far * far pascal AnsiPrev(char far *start, char far *current);
extern char far * far pascal lstrcpy(char far *dest, char far *source);

void far SeparateFile(int unused, char far *dir, char far *name, char far *path)
{
    char save;
    char far *p;
    char far *cut;

    p = path + lstrlen(path);
    while (*p != ':' && *p != 0x5c && p > path)
        p = AnsiPrev(path, p);
    if (*p != ':' && *p != 0x5c) {
        lstrcpy(name, path);
        *dir = 0;
        return;
    }
    cut = p + 1;
    lstrcpy(name, p + 1);
    save = *cut;
    lstrcpy(dir, path);
    *cut = save;
    dir[p - path + 1] = 0;
}
