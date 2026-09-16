#include <iostream>
#include <cmath>
#include <graphics.h>

using namespace std;

void bresenhamCircle(int cx, int cy, int r, int col = WHITE)
{
    int x = 0;
    int y = r;
    int del = 2 * (1 - r);
    int d;

    while (x <= y)
    {
        putpixel(cx + x, cy + y, col);
        putpixel(cx - x, cy + y, col);
        putpixel(cx + x, cy - y, col);
        putpixel(cx - x, cy - y, col);

        putpixel(cx + y, cy + x, col);
        putpixel(cx - y, cy + x, col);
        putpixel(cx + y, cy - x, col);
        putpixel(cx - y, cy - x, col);

        if (del < 0)
        {
            d = 2 * (del + y) - 1;

            if (d <= 0)
            {
                x++;
                del += 2 * x + 1;
            }
            else
            {
                x++;
                y--;
                del += 2 * (x - y + 1);
            }
        }
        else if (del > 0)
        {
            d = 2 * (del - x) - 1;

            if (d <= 0)
            {
                y--;
                del += 1 - 2 * y;
            }
            else
            {
                x++;
                y--;
                del += 2 * (x - y + 1);
            }
        }
        else
        {
            x++;
            y--;
            del += 2 * (x - y + 1);
        }
    }
}

void dda(int x1, int y1, int x2, int y2, int col = WHITE)
{
    float dlx = x2 - x1;
    float dly = y2 - y1;

    int L = (int)fmax(fabs(dlx), fabs(dly));

    if (L == 0)
    {
        putpixel(x1, y1, col);
        return;
    }

    float dx = dlx / L;
    float dy = dly / L;

    float x = x1;
    float y = y1;

    for (int i = 0; i <= L; i++)
    {
        putpixel((int)lround(x), (int)lround(y), col);

        x += dx;
        y += dy;
    }
}

int main()
{
   initwindow(800, 600, "Computer Graphics");

    bresenhamCircle(130, 215, 25, RED);

    dda(135, 215, 155, 215, RED);
    dda(135, 215, 135, 198, RED);
    dda(135, 198, 147, 198, RED);

    bresenhamCircle(74, 215, 8, RED);

    dda(105, 212, 74, 215, RED);
    dda(105, 218, 74, 215, RED);

    dda(130, 190, 130, 180, RED);
    dda(105, 180, 155, 180, RED);

    dda(110, 245, 150, 245, RED);
    dda(117, 238, 117, 245, RED);
    dda(143, 238, 143, 245, RED);

    dda(200, 0, 200, 150, GREEN);
    dda(300, 0, 300, 150, GREEN);
    dda(200, 150, 300, 150, GREEN);

    dda(200, 280, 200, 480, GREEN);
    dda(300, 280, 300, 480, GREEN);
    dda(200, 280, 300, 280, GREEN);

    dda(400, 0, 400, 200, GREEN);
    dda(500, 0, 500, 200, GREEN);

    dda(400, 200, 500, 200, GREEN);

    dda(400, 330, 400, 480, GREEN);
    dda(500, 330, 500, 480, GREEN);
    dda(400, 330, 500, 330, GREEN);

    getch();
    closegraph();

    return 0;
}