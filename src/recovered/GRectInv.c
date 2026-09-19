/* Byte-matched reconstruction; modern filename and isolated translation unit. */
struct Rect { int left,top,right,bottom; };
extern void GInvBox(int,int,int,int);
void GRectInv(struct Rect *r) { if(r) GInvBox(r->left,r->top,r->right,r->bottom); }
