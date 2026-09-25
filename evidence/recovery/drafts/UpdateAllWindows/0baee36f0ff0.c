/*
 * Drain the USER message queue for the update range.  Each retrieved
 * message is immediately handed to UpdateWindow; a failed update stops the
 * loop so the routine returns without spinning on that message.
 */
struct UpdateMessage {
    int window;
    unsigned char rest[16];
};

extern int far pascal PeekMessage(void far *message, int window,
                                  unsigned int first, unsigned int last,
                                  unsigned int remove);
extern int far pascal UpdateWindow(int window);

void UpdateAllWindows(void)
{
    struct UpdateMessage message;

    if (PeekMessage(&message, 0, 0x0f, 0x0f, 1)) {
        do {
            UpdateWindow(message.window);
        } while (PeekMessage(&message, 0, 0x0f, 0x0f, 1));
    }
}
