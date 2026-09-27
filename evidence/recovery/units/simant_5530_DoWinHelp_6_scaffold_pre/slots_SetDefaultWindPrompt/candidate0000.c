/*
 * SetDefaultWindPrompt: seed the message editor with the default prompt
 * position for the current game tool.  While the game is paused (far
 * PACK word GamePaused nonzero) the prompt comes from the far
 * WindPromptStrs table: the yard entry for the no-tool state (-1), the
 * entry for tool 10 and the entry for tool 11.  Any other tool leaves the
 * editor untouched.  When the game is not paused the editor is opened at
 * the zero position.  Every call passes the fixed -2/-1 pair and the
 * caller's mode word straight through to EditMessage.
 */
struct WindPromptTable {
    int header[4];
    long yardPrompt;        /* +8  */
    long toolTenPrompt;     /* +0xc */
    int filler[26];
    long toolElevenPrompt;  /* +0x44 */
};

extern int far GamePaused;
extern int far CurGameTool;
extern struct WindPromptTable far * far WindPromptStrs;
extern void far EditMessage(long position, int a, int b, int mode);

void far SetDefaultWindPrompt(int mode)
{
    if (GamePaused == 0)
        EditMessage(0L, -2, -1, mode);
    else if (CurGameTool == -1)
        EditMessage(WindPromptStrs->yardPrompt, -2, -1, mode);
    else if (CurGameTool == 10)
        EditMessage(WindPromptStrs->toolTenPrompt, -2, -1, mode);
    else if (CurGameTool == 11)
        EditMessage(WindPromptStrs->toolElevenPrompt, -2, -1, mode);
}
