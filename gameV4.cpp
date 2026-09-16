#include <iostream>
#include <graphics.h>
#include <stack>
#include <cstdlib>

using namespace std;

void bresenhamLine(int x1, int y1, int x2, int y2, int color)
{
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);

    int sx = (x2 >= x1) ? 1 : -1;
    int sy = (y2 >= y1) ? 1 : -1;

    int x = x1;
    int y = y1;

    if (dx >= dy)
    {
        int p = 2 * dy - dx;

        for (int i = 0; i <= dx; i++)
        {
            putpixel(x, y, color);

            if (p < 0)
            {
                x += sx;
                p += 2 * dy;
            }
            else
            {
                x += sx;
                y += sy;
                p += 2 * (dy - dx);
            }
        }
    }
    else
    {
        int p = 2 * dx - dy;

        for (int i = 0; i <= dy; i++)
        {
            putpixel(x, y, color);

            if (p < 0)
            {
                y += sy;
                p += 2 * dx;
            }
            else
            {
                x += sx;
                y += sy;
                p += 2 * (dx - dy);
            }
        }
    }
}

void drawCircle(int cx, int cy, int r, int color)
{
    int x = 0;
    int y = r;
    int d = 2 * (1 - r);

    while (y >= 0)
    {
        putpixel(cx + x, cy + y, color);
        putpixel(cx - x, cy + y, color);
        putpixel(cx + x, cy - y, color);
        putpixel(cx - x, cy - y, color);
        putpixel(cx + y, cy + x, color);
        putpixel(cx - y, cy + x, color);
        putpixel(cx + y, cy - x, color);
        putpixel(cx - y, cy - x, color);

        if (d < 0)
        {
            int d1 = 2 * d + 2 * y - 1;

            if (d1 <= 0)
            {
                x++;
                d += 2 * x + 1;
            }
            else
            {
                x++;
                y--;
                d += 2 * x - 2 * y + 2;
            }
        }
        else if (d > 0)
        {
            int d2 = 2 * d - 2 * x - 1;

            if (d2 <= 0)
            {
                x++;
                y--;
                d += 2 * x - 2 * y + 2;
            }
            else
            {
                y--;
                d -= 2 * y - 1;
            }
        }
        else
        {
            x++;
            y--;
            d += 2 * x - 2 * y + 2;
        }
    }
}

void seedFill(int x, int y, int oldColor, int newColor)
{
    if (oldColor == newColor)
        return;

    stack<pair<int, int>> s;
    s.push({x, y});

    while (!s.empty())
    {
        int px = s.top().first;
        int py = s.top().second;
        s.pop();

        if (px < 0 || px > getmaxx() ||
            py < 0 || py > getmaxy())
            continue;

        if (getpixel(px, py) != oldColor)
            continue;

        putpixel(px, py, newColor);

        s.push({px + 1, py});
        s.push({px - 1, py});
        s.push({px, py + 1});
        s.push({px, py - 1});
    }
}

int main()
{
    int gd = DETECT;
    int gm;

    char path[] = "";
    initgraph(&gd, &gm, path);

    cleardevice();

    int green = GREEN;
    int white = WHITE;

    bresenhamLine(200, 0, 300, 0, green);
    bresenhamLine(300, 0, 300, 150, green);
    bresenhamLine(300, 150, 200, 150, green);
    bresenhamLine(200, 150, 200, 0, green);

    bresenhamLine(200, 280, 300, 280, green);
    bresenhamLine(300, 280, 300, 480, green);
    bresenhamLine(300, 480, 200, 480, green);
    bresenhamLine(200, 480, 200, 280, green);

    bresenhamLine(400, 0, 500, 0, green);
    bresenhamLine(500, 0, 500, 200, green);
    bresenhamLine(500, 200, 400, 200, green);
    bresenhamLine(400, 200, 400, 0, green);

    bresenhamLine(400, 330, 500, 330, green);
    bresenhamLine(500, 330, 500, 480, green);
    bresenhamLine(500, 480, 400, 480, green);
    bresenhamLine(400, 480, 400, 330, green);

    seedFill(250, 100, getpixel(250, 100), GREEN);
    seedFill(250, 350, getpixel(250, 350), GREEN);
    seedFill(450, 100, getpixel(450, 100), GREEN);
    seedFill(450, 400, getpixel(450, 400), GREEN);

    drawCircle(130, 215, 25, white);

    bresenhamLine(135, 215, 155, 215, white);
    bresenhamLine(155, 215, 135, 198, white);
    bresenhamLine(135, 198, 135, 215, white);

    bresenhamLine(105, 212, 74, 215, white);
    bresenhamLine(74, 215, 105, 218, white);
    bresenhamLine(105, 218, 105, 212, white);

    bresenhamLine(130, 190, 130, 180, white);
    bresenhamLine(105, 180, 155, 180, white);

    bresenhamLine(110, 245, 150, 245, white);
    bresenhamLine(117, 238, 117, 245, white);
    bresenhamLine(143, 238, 143, 245, white);

    seedFill(130, 215, getpixel(130, 215), RED);
    seedFill(95, 215, getpixel(95, 215), YELLOW);

    getch();
    closegraph();

    return 0;
}