#include <iostream>
#include <graphics.h>
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

void seedFill(int x, int y, int oldColor, int newColor)
{
    if (getpixel(x, y) != oldColor)
        return;

    putpixel(x, y, newColor);

    seedFill(x + 1, y, oldColor, newColor);
    seedFill(x - 1, y, oldColor, newColor);
    seedFill(x, y + 1, oldColor, newColor);
    seedFill(x, y - 1, oldColor, newColor);
}

int main()
{
    int n;
    int x[20], y[20];
    int seedX, seedY;
    int color;

    cout << "Enter number of points: ";
    cin >> n;

    cout << "Enter coordinates:\n";

    for (int i = 0; i < n; i++)
    {
        cout << "Point " << i + 1 << ": ";
        cin >> x[i] >> y[i];
    }

    cout << "Enter seed pixel coordinates: ";
    cin >> seedX >> seedY;

    cout << "Enter fill color: ";
    cin >> color;

    int gd = DETECT, gm;
    char path[] = "";

    initgraph(&gd, &gm, path);

    for (int i = 0; i < n; i++)
    {
        int j = (i + 1) % n;
        bresenhamLine(x[i], y[i], x[j], y[j], WHITE);
    }

    int oldColor = getpixel(seedX, seedY);

    if (oldColor != color)
        seedFill(seedX, seedY, oldColor, color);

    cout << "Press Enter to exit...";
    cin.ignore();
    cin.get();

    closegraph();

    return 0;
}