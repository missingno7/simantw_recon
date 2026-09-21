/*
 * Hypothesis: start at USER's top window, skip hidden windows with the
 * historical forward relation 2, then return the second relation-4 window
 * only when the first relation-4 query succeeds.  The target's caller-cleaned
 * retf makes this wrapper C-style far, while USER imports are Pascal far.
 */
extern int far pascal GetTopWindow(int window);
extern int far pascal IsWindowVisible(int window);
extern int far pascal GetNextWindow(int window, int relation);
extern int far pascal GetWindow(int window, int relation);

int far MyGetTopWindow(int window)
{
    register int topWindow;
    int resultWindow;

    topWindow = GetTopWindow(window);
    if (topWindow == 0)
        return 0;
    do {
        if (IsWindowVisible(topWindow))
            break;
        topWindow = GetNextWindow(topWindow, 2);
    } while (topWindow != 0);

    if (topWindow == 0)
        return 0;
    if (GetWindow(topWindow, 4) == 0)
        return 0;
    resultWindow = GetWindow(topWindow, 4);
    topWindow = resultWindow;
    return topWindow;
}
