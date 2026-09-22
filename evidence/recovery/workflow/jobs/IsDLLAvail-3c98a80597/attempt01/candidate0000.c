/* IsDLLAvail: probe three candidate directories for a file named by the
 * caller's far string (name): the system directory, the Windows
 * directory, and the running EXE's own directory (via GetModuleFileName
 * + strrchr to strip the filename).  Each candidate directory gets a
 * trailing backslash appended only if it does not already end with one,
 * then name is appended and access(path,0) probes existence.  The first
 * two probes return 1 immediately on success; the third probe returns
 * 1/0 from the access() result directly.
 */

extern int near hInst;

extern int far access(char far *path, int mode);
extern char far * far strrchr(const char far *text, int character);

extern int far pascal GetSystemDirectory(char far *buf, unsigned int size);
extern int far pascal GetWindowsDirectory(char far *buf, unsigned int size);
extern unsigned int far pascal GetModuleFileName(int hInstance, char far *buf, unsigned int size);
extern char far * far pascal lstrcat(char far *dest, const char far *src);

int far IsDLLAvail(char far *name)
{
    char buf[0x100];
    char far *p;

    GetSystemDirectory(buf, 0x100);
    for (p = buf; *p; p++)
        ;
    if (*(p - 1) != '\\')
        lstrcat(buf, "\\");
    lstrcat(buf, name);
    if (access(buf, 0) == 0)
        return 1;

    GetWindowsDirectory(buf, 0x100);
    for (p = buf; *p; p++)
        ;
    if (*(p - 1) != '\\')
        lstrcat(buf, "\\");
    lstrcat(buf, name);
    if (access(buf, 0) == 0)
        return 1;

    GetModuleFileName(hInst, buf, 0x100);
    p = strrchr(buf, '\\');
    *p = 0;
    lstrcat(buf, "\\");
    lstrcat(buf, name);
    return (access(buf, 0) == 0) ? 1 : 0;
}
