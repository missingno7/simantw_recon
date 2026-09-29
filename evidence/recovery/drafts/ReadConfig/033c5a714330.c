/*
 * Hypothesis: configFileName is a far pointer object in the selector-backed
 * data segment; its stored far pointer is passed to _lopen. The routine reads
 * two whitespace-delimited fields, maps the first field's initial to a display
 * type, and stores a numeric second field as musicDevice.
 */
extern char far * __based(__segname("SIMANT_DATA_GROUP")) configFileName;
extern char far * __based(__segname("SIMANT_DATA_GROUP")) configFileMissingStr;
extern int near rootWnd;
extern unsigned char near displayType;
extern int near musicDevice;
extern int far pascal _lopen(char far *name, int mode);
extern int far read(int fd, void far *buffer, unsigned int count);
extern int far pascal _lclose(int fd);
extern int far isspace(int character);
extern int far isdigit(int character);
extern int far pascal MessageBox(int window, char far *text,
                                 char far *caption, unsigned style);

extern void far exit(int status);

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
        do {
            p = buffer;
            while (read(fd, &c, 1) && isspace(c))
                ;
            do {
                *p++ = c;
            } while (read(fd, &c, 1) && !isspace(c));
            *p = 0;
            --count;
        } while (count != 0);
        read(fd, &first, 1);
        count = 2;
        p = buffer;
        while (read(fd, &c, 1) && isspace(c))
            ;
        do {
            *p++ = c;
        } while (read(fd, &c, 1) && !isspace(c));
        *p = 0;
        read(fd, &digit, 1);
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
            goto config_error;
        }
        if (isdigit(digit))
            musicDevice = digit - '0';
    goto done;

config_error:
    MessageBox(rootWnd, errorText, "Message", 0x30);
    exit(1);

done:
    ;
}
