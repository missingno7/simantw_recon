/* Recovery candidate: modern filename; historical source unavailable. */
struct Rect { int left,top,right,bottom; };
extern void GInvBox(int,int,int,int);
void GRectInv(struct Rect *r) { if(r) GInvBox(r->left,r->top,r->right,r->bottom); }
