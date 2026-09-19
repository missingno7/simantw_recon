/* Candidate reconstruction of the text-box coordinate adapter. */
extern void far GBoxFill(int left, int top, int right, int bottom, int color);

void GTextBox(int left, int top, int right, int bottom, int color)
{
    GBoxFill(left << 3, top, right << 3, bottom + 1, color);
}
