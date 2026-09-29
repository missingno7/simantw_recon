/* Semantic reconstruction: require both a populated HWND slot and a true USER
 * zoom predicate; the short-circuit preserves the empty-slot fast path. */
extern int near win_hwnd[];
extern int far pascal IsZoomed(int window);
int win_IsWinZoomed(int window)
{
  int near * volatile windowHome;
  windowHome = &win_hwnd[window >> 8];
  if ((*(&win_hwnd[window >> 8])) != 0 && IsZoomed(*(&win_hwnd[window >> 8])) != 0)
    return 1;
  return 0;
}
