#include <iostream>
#include <graphics.h>
#include <cmath>
#include <cstdlib>

using namespace std;

void translation(int s[3][3], int size, int tx, int ty)
{
    int result[3][3];

    int T[3][3] = {
        {1, 0, 0},
        {0, 1, 0},
        {tx, ty, 1}
    };

    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            result[i][j] = 0;

            for (int k = 0; k < 3; k++)
            {
                result[i][j] += s[i][k] * T[k][j];
            }
        }
    }

    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            s[i][j] = result[i][j];
        }
    }
}

void scale(int s[3][3], int size, float sx, float sy)
{
    float scale_matrix[3][3] = {
        {sx, 0, 0},
        {0, sy, 0},
        {0, 0, 1}
    };

    float result[3][3];

    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            result[i][j] = 0;

            for (int k = 0; k < 3; k++)
            {
                result[i][j] += s[i][k] * scale_matrix[k][j];
            }
        }
    }

    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            s[i][j] = (int)result[i][j];
        }
    }
}

void rotate(int s[3][3], int size, int angle)
{
    float angle_rad = angle * (M_PI / 180.0);

    float cosX = cos(angle_rad);
    float sinX = sin(angle_rad);

    float R[3][3] = {
        {cosX, sinX, 0},
        {-sinX, cosX, 0},
        {0, 0, 1}
    };

    float result[3][3];

    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            result[i][j] = 0;

            for (int k = 0; k < 3; k++)
            {
                result[i][j] += s[i][k] * R[k][j];
            }
        }
    }

    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            s[i][j] = (int)result[i][j];
        }
    }
}

void drawPixel(int x, int y, int color)
{
    if (x >= 0 && x <= getmaxx() &&
        y >= 0 && y <= getmaxy())
    {
        putpixel(x, y, color);
    }
}

void dda(int x1, int y1, int x2, int y2, int color)
{
    int length = max(abs(x2 - x1), abs(y2 - y1));

    if (length == 0)
    {
        drawPixel(x1, y1, color);
        return;
    }

    float dx = (float)(x2 - x1) / length;
    float dy = (float)(y2 - y1) / length;

    float x = x1;
    float y = y1;

    for (int i = 0; i <= length; i++)
    {
        drawPixel((int)x, (int)y, color);

        x += dx;
        y += dy;
    }
}

void plot(int s[3][3], int color)
{
    dda(s[0][0], s[0][1],
        s[1][0], s[1][1], color);

    dda(s[0][0], s[0][1],
        s[2][0], s[2][1], color);

    dda(s[1][0], s[1][1],
        s[2][0], s[2][1], color);
}

int main()
{
    int size = 3;

    int s[3][3] = {
        {150, 200, 1},
        {100, 300, 1},
        {325, 125, 1}
    };

    int tx, ty;
    float sx, sy;
    int angle;

    cout << "Enter displacement in x: ";
    cin >> tx;

    cout << "Enter displacement in y: ";
    cin >> ty;

    cout << "Enter scaling factor in x: ";
    cin >> sx;

    cout << "Enter scaling factor in y: ";
    cin >> sy;

    cout << "Enter theta in degrees: ";
    cin >> angle;

    int gd = DETECT;
    int gm;

    initgraph(&gd, &gm, NULL);

    plot(s, 2);

    translation(s, size, tx, ty);
    plot(s, 5);

    scale(s, size, sx, sy);
    plot(s, 8);

    rotate(s, size, angle);
    plot(s, 7);

    getch();
    closegraph();

    return 0;
}
