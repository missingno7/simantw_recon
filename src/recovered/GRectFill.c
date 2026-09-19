/* Byte-matched reconstruction; modern filename and isolated translation unit. */
struct Rect { int left,top,right,bottom; };
extern void GBoxFill(int,int,int,int,int);
void GRectFill(struct Rect *r,int color) { if(r) GBoxFill(r->left,r->top,r->right,r->bottom,color); }
