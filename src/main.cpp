#include <stdint.h>
#include <cstdio>
#include <complex>
#include <cmath>
#include <math.h>

// function 
void gradient(int H, int W, int choice) {
   unsigned char buffer[H][W];
   unsigned char outimg[H][W];
   int addedx = 0, addedy = 0, addedxx = 0, addedyy = 0;
   double sqrx = 0, sqry = 0, grad = 0, sqrxx = 0, sqryy = 0, grad2 = 0;
   int yfilter[9] = {-1,0,1,-2,0,2,-1,0,1};
   int xfilter[9] = {-1, -2, -1, 0, 0, 0, 1, 2, 1};
   int yfive[25] = {-1, -2, 0, 2, 1, -2, -4, 0, 4, 2, -4, -8, 0, 8, 4, -2, -4, 0, 4, 2, -1, -2, 0, 2, 1};
   int xfive[25] = {1, 2, 4, 2 ,1, 2, 4, 8, 4, 2, 0, 0, 0, 0, 0, -2, -4, -8, -4, -2, -1, -2, -4 -2, -1};
   int x = 0, y = 0, xx = 0, yy = 0;
   int ax = 0, ay = 0, bx = 0, by = 0, cx = 0, cy = 0, dx = 0, dy = 0, ex = 0, ey = 0, fx = 0, fy = 0, gx = 0, gy = 0, hx = 0, hy = 0, ix = 0, iy = 0;
   int jx= 0, jy= 0, kx= 0, ky= 0, lx= 0, ly= 0, mx= 0, my= 0, nx= 0, ny= 0, ox= 0, oy= 0, px= 0, py= 0, qx= 0, qy= 0, rx= 0, ry= 0, sx= 0, sy= 0, tx= 0, ty= 0, ux= 0, uy= 0, vx= 0, vy= 0, wx= 0, wy= 0, zx= 0, zy= 0, axx= 0, ayy = 0;
   
    //manually change depending on image raw being manipulated
   FILE * fp = fopen("beach.raw", "rb");
   fread(buffer, H*W, 1, fp);

    //loops through images and writes to output files
    //int p = 0, pl = 0, pr = 0, pu = 0, pd = 0, ptl = 0, ptopr = 0, pbl = 0, pbr = 0;

     for(y = 0; y < H; y++){
        for(x = 0; x < W; x++){
            //these hold the value of an images pixel and set bounds for operations
            //instead of 0 for bounds checking maybe assign 128
            if(choice == 0){
            //set to 0 if out of bounds
            if((y-1) < 0 || (y-1) >= H || (x-1) < 0 || (x-1) >= W){
                ax = 128;
                ay = 128;
            }
            else{
                ax = buffer[y-1][x-1] * xfilter[0];
                ay = buffer[y-1][x-1] * yfilter[0];
            }
            if((y-1) < 0 || (y-1) >= H || (x) < 0 || (x) >= W){
                bx = 128;
                by = 128;
            }
            else{
                bx = buffer[y-1][x] * xfilter[1];
                by = buffer[y-1][x] * yfilter[1];
            }
            if((y-1) < 0 || (y-1) >= H || (x+1) < 0 || (x+1) >= W){
                cx = 128;
                cy = 128;
            }
            else{
                cx = buffer[y-1][x+1] * xfilter[2];
                cy = buffer[y-1][x+1] * yfilter[2];
            }
            if((y) < 0 || (y) >= H || (x-1) < 0 || (x-1) >= W){
                dx = 128;
                dy = 128;
            }
            else{
                dx = buffer[y][x-1] * xfilter[3];
                dy = buffer[y][x-1] * yfilter[3];
            }
            if((y) < 0 || (y) >= H || (x) < 0 || (x) >= W){
                ex = 128;
                ey = 128;
            }
            else{
                ex = buffer[y][x] * xfilter[4];
                ey = buffer[y][x] * yfilter[4];
            }
            if((y) < 0 || (y) >= H || (x+1) < 0 || (x+1) >= W){
                fx = 128;
                fy = 128;
            }
            else{
                fx = buffer[y][x+1] * xfilter[5];
                fy = buffer[y][x+1] * yfilter[5];
            }
            if((y+1) < 0 || (y+1) >= H || (x-1) < 0 || (x-1) >= W){
                gx = 128;
                gy = 128;
            }
            else{
                gx = buffer[y+1][x-1] * xfilter[6];
                gy = buffer[y+1][x-1] * yfilter[6];
            }
            if((y+1) < 0 || (y+1) >= H || (x) < 0 || (x) >= W){
                hx = 128;
                hy = 128;
            }
            else{
                hx = buffer[y+1][x] * xfilter[7];
                hy = buffer[y+1][x] * yfilter[7];
            }
            if((y+1) < 0 || (y+1) >= H || (x+1) < 0 || (x+1) >= W){
                ix = 128;
                iy = 128;
            }
            else{
                ix = buffer[y+1][x+1] * xfilter[8];
                iy = buffer[y+1][x+1] * yfilter[8];
            }
            //get rid of 128
            addedx = (ax + bx + cx + dx + ex + fx + gx + hx + ix) / 8 + 128;
            addedy = (ay + by + cy + dy + ey + fy + gy + hy + iy) / 8 + 128;
            sqrx = pow(addedx,2);
            sqry = pow(addedy,2);
            grad = sqrt(sqrx + sqry);
            //assigning result to single pixel
            outimg[y][x] = grad;
            }
            else{
                if((y - 2 < 0 || (y+2) > H || (x-2) < 0 || (x+2) > W)){
                    addedxx = 128;
                    addedyy = 128;
                }
                else{
                    ax = buffer[y-2][x-2] * xfive[0];
                    ay = buffer[y-2][x-2] * yfive[0];
                    bx = buffer[y-2][x-1] * xfive[1];
                    by = buffer[y-2][x-1] * yfive[1];
                    cx = buffer[y-2][x] * xfive[2];
                    cy = buffer[y-2][x] * yfive[2];
                    dx = buffer[y-2][x+1] * xfive[3];
                    dy = buffer[y-2][x+1] * yfive[3];
                    ex = buffer[y-2][x+2] * xfive[4];
                    ey = buffer[y-2][x+2] * yfive[4];
                    fx = buffer[y-1][x-2] * xfive[5];
                    fy = buffer[y-1][x-2] * yfive[5];
                    gx = buffer[y-1][x-1] * xfive[6];
                    gy = buffer[y-1][x-1] * yfive[6];
                    hx = buffer[y-1][x] * xfive[7];
                    hy = buffer[y-1][x] * yfive[7];
                    ix = buffer[y-1][x+1] * xfive[8];
                    iy = buffer[y-1][x+1] * yfive[8];
                    jx = buffer[y-1][x+2] * xfive[9];
                    jy = buffer[y-1][x+2] * yfive[9];
                    kx = buffer[y][x-2] * xfive[10];
                    ky = buffer[y][x-2] * yfive[10];
                    lx = buffer[y][x-1] * xfive[11];
                    ly = buffer[y][x-1] * yfive[11];
                    mx = buffer[y][x] * xfive[12];
                    my = buffer[y][x] * yfive[12];
                    nx = buffer[y][x+1] * xfive[13];
                    ny = buffer[y][x+1] * yfive[13];
                    ox = buffer[y][x+2] * xfive[14];
                    oy = buffer[y][x+2] * yfive[14];
                    px = buffer[y+1][x-2] * xfive[15];
                    py = buffer[y+1][x-2] * yfive[15];
                    qx = buffer[y+1][x-1] * xfive[16];
                    qy = buffer[y+1][x-1] * yfive[16];
                    rx = buffer[y+1][x] * xfive[17];
                    ry = buffer[y+1][x] * yfive[17];
                    sx = buffer[y+1][x+1] * xfive[18];
                    sy = buffer[y+1][x+1] * yfive[18];
                    tx = buffer[y+1][x+2] * xfive[19];
                    ty = buffer[y+1][x+2] * yfive[19];
                    ux = buffer[y+2][x-2] * xfive[20];
                    uy = buffer[y+2][x-2] * yfive[20];
                    vx = buffer[y+2][x-1] * xfive[21];
                    vy = buffer[y+2][x-1] * yfive[21];
                    wx = buffer[y+2][x] * xfive[22];
                    wy = buffer[y+2][x] * yfive[22];
                    zx = buffer[y+2][x+1] * xfive[23];
                    zy = buffer[y+2][x+1] * yfive[23];
                    axx = buffer[y+2][x+2] * xfive[24];
                    ayy = buffer[y+2][x+2] * yfive[24];
                    addedxx = (ax + bx + cx + dx + ex + fx + gx + hx + ix + jx + kx + lx + mx + nx + ox + px + qx + rx + sx + tx + ux + vx + wx + zx + axx) / 60 + 128;
                    addedyy = (ay + by + cy + dy + ey + fy + gy + hy + iy + jy + ky + ly + my + ny + oy + py + qy + ry + sy + ty + uy + vy + wy + zy + ayy) / 60 + 128;
                }
            
            
            sqrxx = pow(addedxx,2);
            sqryy = pow(addedyy,2);
            grad2 = sqrt(sqrxx + sqryy);
            outimg[y][x] = grad2;
            }
            
        }
    }
    //manually change output to filter choice raw
    FILE * fp2 = fopen("beachgrad5.raw", "wb");

    fwrite(outimg, H*W, 1, fp2);

    fclose(fp);
    fclose(fp2);
    return;
}

int main(){
    //height and width of image
    int imgH = 500;
    int imgW = 750;

    gradient(imgH, imgW, 1);
    
    return 0;
}
