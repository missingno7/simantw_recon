/* Invalidate only cells inside the editor view, advancing the far map pointer by row. */
extern int near tileHeight[5]; extern int near editWidth; extern int near editHeight;
typedef int far * PInt;
void far InvalEuMap(int left,int top,int right,int bottom) {
    int row; int cell; int rowStart; PInt p;
    if(left<0) left=0; else if(right>127) right=127;
    if(top<0) top=0; else if(bottom>63) bottom=63;
    for(row=top; row<=bottom; ++row) {
        rowStart=editWidth*row+left; p=*(PInt near *)&tileHeight[3]; p+=rowStart;
        for(cell=left; cell<=right; ++cell,++p) {
            if(cell>=0 && cell<editWidth && row>=0 && row<editHeight) *p=-1;
        }
    }
}
