/* Continuation of the typedb-clean two-API source with the second count loop. */
extern char far * __based(__segname("SIMANT_DATA_GROUP")) configFileName;
extern char far * __based(__segname("SIMANT_DATA_GROUP")) configFileMissingStr;
extern int near rootWnd;
extern unsigned char near displayType;
extern int near musicDevice;
extern int far pascal _lopen(char far *name, int mode);
extern int far read(int fd, void far *buffer, unsigned int count);
extern int far pascal _lread(int fd, void far *buffer, int count);
extern int far pascal _lclose(int fd);
extern int far isspace(int character);
extern int far isdigit(int character);
extern int far pascal MessageBox(int window, char far *text,
                                 char far *caption, unsigned style);
extern void far _exit(int status);

void far ReadConfig(void)
{
    int fd;
    int count;
    char buffer[30];
    char c;
    char *p;
    char first;
    char digit;
    char far *errorText;

    fd = _lopen(configFileName, 0);
    if (fd <= 0) {
        errorText = configFileMissingStr;
        goto config_error;
    }
    count = 2;
    while (count--) {
        p = buffer;
        while (read(fd, &c, 1) && isspace(c))
            ;
        do {
            *p++ = c;
        } while (read(fd, &c, 1) && !isspace(c));
        *p = 0;
    }
    _lread(fd, &first, 1);
    count = 2;
    while (count--) {
        p = buffer;
        while (read(fd, &c, 1) && isspace(c))
            ;
        do {
            *p++ = c;
        } while (read(fd, &c, 1) && !isspace(c));
        *p = 0;
    }
    _lread(fd, &digit, 1);
    _lclose(fd);

    switch (first) {
    case '?': displayType = 0xff; break;
    case 'E': displayType = 0; break;
    case 'H': displayType = 3; break;
    case 'M': displayType = 5; break;
    case 'T': displayType = 2; break;
    case 'V': displayType = 8; break;
    case 'W': displayType = 10; break;
    case 'e': displayType = 4; break;
    case 'm': displayType = 7; break;
    case 'w': displayType = 9; break;
    default:
        errorText = "Bad 'Display Mode' in configuration file";
config_error:
        MessageBox(rootWnd, errorText, "Message", 0x30);
        _exit(1);
        break;
    }
    if (isdigit(digit))
        musicDevice = digit - '0';
    goto done;

done:
    ;
}
