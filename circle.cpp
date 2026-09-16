#include <graphics.h>
#include <iostream>

using namespace std;

void plotCircle(int xc, int yc, int x, int y)
{
    putpixel(xc + x, yc + y, WHITE);
    putpixel(xc - x, yc + y, WHITE);
    putpixel(xc + x, yc - y, WHITE);
    putpixel(xc - x, yc - y, WHITE);

    putpixel(xc + y, yc + x, WHITE);
    putpixel(xc - y, yc + x, WHITE);
    putpixel(xc + y, yc - x, WHITE);
    putpixel(xc - y, yc - x, WHITE);

    putpixel(x, y, WHITE);
    putpixel(-x, y, WHITE);
    putpixel(x, -y, WHITE);
    putpixel(-x, -y, WHITE);

    putpixel(y, x, WHITE);
    putpixel(-y, x, WHITE);
    putpixel(y, -x, WHITE);
    putpixel(-y, -x, WHITE);
}

int main()
{
    int r, xc, yc;

    cout << "Enter Center X: ";
    cin >> xc;

    cout << "Enter Center Y: ";
    cin >> yc;

    cout << "Enter Radius: ";
    cin >> r;

    int gd = DETECT, gm;
    initgraph(&gd, &gm, NULL);

    int x = 0;
    int y = r;
    int delta = 2 * (1 - r);
    int d;

    while (y >= 0)
    {
        plotCircle(xc, yc, x, y);

        if (delta < 0)
        {
            d = 2 * delta + 2 * y - 1;

            if (d <= 0)
            {
                x++;
                delta = delta + 2 * x + 1;
            }
            else
            {
                x++;
                y--;
                delta = delta + 2 * x - 2 * y + 2;
            }
        }
        else if (delta > 0)
        {
            d = 2 * delta - 2 * x - 1;

            if (d <= 0)
            {
                x++;
                y--;
                delta = delta + 2 * x - 2 * y + 2;
            }
            else
            {
                y--;
                delta = delta - 2 * y + 1;
            }
        }
        else
        {
            x++;
            y--;
            delta = delta + 2 * x - 2 * y + 2;
        }
           delay(50);
    }
    putpixel(xc,yc,WHITE);
    getch();
    closegraph();

    return 0;
}

