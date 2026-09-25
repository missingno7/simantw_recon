/*
 * Hypothesis: DoNextWindow walks forward from a non-null window handle until
 * USER reports no further window.  It then rejects owned or hidden windows by
 * walking in the opposite direction, and finally raises the first remaining
 * visible top-level window.  The numeric relations are the historical USER
 * constants used by this module: 2 for the forward walk, 4 for the owner
 * query, and 3 for the reverse walk.
 */
extern int far pascal GetNextWindow(int window, int relation);
extern int far pascal GetWindow(int window, int relation);
extern int far pascal IsWindowVisible(int window);
extern void far pascal BringWindowToTop(int window);

void DoNextWindow(int window)
{
    int nextWindow;

    if (window == 0)
        return;

    while ((nextWindow = GetNextWindow(window, 2)) != 0)
        window = nextWindow;

    while (GetWindow(window, 4) != 0 || !IsWindowVisible(window))
        window = GetNextWindow(window, 3);

    BringWindowToTop(window);
}
