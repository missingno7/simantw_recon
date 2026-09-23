/*
 * Hypothesis: read the configuration file as whitespace-delimited words. The
 * first word selects the display type and the second, when numeric, selects
 * the music device. The file name and missing-file text are far globals.
 */
extern char far * far configFileName;
extern char far * far configFileMissingStr;
extern int near rootWnd;
extern unsigned char near displayType;
extern int near musicDevice;
extern int far lopen(char far *name, int mode);
extern int far read(int fd, void far *buffer, unsigned int count);
extern int far lclose(int fd);
extern int far isspace(int character);
extern int far isdigit(int character);
extern int far messageBox(int near hwnd, char far *text, char far *caption, unsigned int type);
extern void far exit(int status);

void far ReadConfig(void)
{
    int fd;
    char first[42];
    char second[42];
    char c;
    char *p;

    fd = lopen(configFileName, 0);
    if (fd > 0) {
        p = first;
        while (read(fd, &c, 1) && isspace(c))
            ;
        while (c && !isspace(c)) {
            *p++ = c;
            if (!read(fd, &c, 1))
                break;
        }
        *p = 0;

        p = second;
        while (read(fd, &c, 1) && isspace(c))
            ;
        while (c && !isspace(c)) {
            *p++ = c;
            if (!read(fd, &c, 1))
                break;
        }
        *p = 0;
        lclose(fd);

        switch (first[0]) {
        case '?': displayType = 0xff; break;
        case '@': displayType = 0; break;
        case 'T': displayType = 3; break;
        case 'S': displayType = 5; break;
        case 'F': displayType = 2; break;
        case 'V': displayType = 8; break;
        case 'W': displayType = 10; break;
        case 'G': displayType = 4; break;
        case 'O': displayType = 7; break;
        case 'Y': displayType = 9; break;
        default:
            messageBox(rootWnd, configFileMissingStr, "Invalid config", 0x30);
            exit(1);
        }
        if (isdigit(second[0]))
            musicDevice = second[0] - '0';
    }
}
