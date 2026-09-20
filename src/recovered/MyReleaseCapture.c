extern int far captureWnd;
extern int far activeAppFlag;
extern void far pascal ReleaseCapture(void);

void MyReleaseCapture(void)
{
    captureWnd = 0;
    if (activeAppFlag)
        ReleaseCapture();
}
