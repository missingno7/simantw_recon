/* Byte-matched C reconstruction. Modern filename and isolated translation unit.
 * Historical source text and declaration spelling are not uniquely recovered. */
struct R { int left,top,right,bottom; };
void win_SortRect(struct R *p) { int t; t=p->left; if(t>p->right) { p->left=p->right;p->right=t; } t=p->top; if(t>p->bottom) { p->top=p->bottom;p->bottom=t; } }
