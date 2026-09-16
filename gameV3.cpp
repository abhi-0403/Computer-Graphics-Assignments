#include <iostream>
#include <graphics.h>
#include <cmath>

using namespace std;

struct Point
{
    float x;
    float y;
};

struct Matrix
{
    float m[3][3];
};

Matrix identity()
{
    Matrix M = {{
        {1, 0, 0},
        {0, 1, 0},
        {0, 0, 1}
    }};

    return M;
}

Matrix multiply(Matrix A, Matrix B)
{
    Matrix C = {};

    for(int i = 0; i < 3; i++)
    {
        for(int j = 0; j < 3; j++)
        {
            for(int k = 0; k < 3; k++)
            {
                C.m[i][j] += A.m[i][k] * B.m[k][j];
            }
        }
    }

    return C;
}

Matrix translationMatrix(float tx, float ty)
{
    Matrix T = identity();

    T.m[2][0] = tx;
    T.m[2][1] = ty;

    return T;
}

Matrix scalingMatrix(float sx, float sy)
{
    Matrix S = {{
        {sx, 0, 0},
        {0, sy, 0},
        {0, 0, 1}
    }};

    return S;
}

Matrix rotationMatrix(float angle)
{
    float rad = angle * 3.14159265f / 180.0f;

    float c = cos(rad);
    float s = sin(rad);

    Matrix R = {{
        {c, s, 0},
        {-s, c, 0},
        {0, 0, 1}
    }};

    return R;
}

Point transform(Point p, Matrix M)
{
    Point q;

    q.x = p.x * M.m[0][0]
        + p.y * M.m[1][0]
        + M.m[2][0];

    q.y = p.x * M.m[0][1]
        + p.y * M.m[1][1]
        + M.m[2][1];

    return q;
}

void drawPixel(int x, int y, int color)
{
    if(x >= 0 && x <= getmaxx() &&
       y >= 0 && y <= getmaxy())
    {
        putpixel(x, y, color);
    }
}

void dda(float x1, float y1,
         float x2, float y2,
         int color)
{
    float dx = x2 - x1;
    float dy = y2 - y1;

    float length;

    if(fabs(dx) > fabs(dy))
        length = fabs(dx);
    else
        length = fabs(dy);

    if(length == 0)
    {
        drawPixel(round(x1), round(y1), color);
        return;
    }

    float xIncrement = dx / length;
    float yIncrement = dy / length;

    float x = x1;
    float y = y1;

    for(int i = 0; i <= (int)length; i++)
    {
        drawPixel(round(x), round(y), color);

        x += xIncrement;
        y += yIncrement;
    }
}

void drawCircle(int cx, int cy, int r, int color)
{
    int x = 0;
    int y = r;

    int del = 2 * (1 - r);
    int d;

    while(x <= y)
    {
        putpixel(cx + x, cy + y, color);
        putpixel(cx - x, cy + y, color);
        putpixel(cx + x, cy - y, color);
        putpixel(cx - x, cy - y, color);

        putpixel(cx + y, cy + x, color);
        putpixel(cx - y, cy + x, color);
        putpixel(cx + y, cy - x, color);
        putpixel(cx - y, cy - x, color);

        if(del < 0)
        {
            d = 2 * (del + y) - 1;

            if(d <= 0)
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
        else if(del > 0)
        {
            d = 2 * (del - x) - 1;

            if(d <= 0)
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

void drawOriginalHelicopter()
{
    drawCircle(130, 215, 25, RED);

    dda(135, 215, 155, 215, RED);
    dda(135, 215, 135, 198, RED);
    dda(135, 198, 147, 198, RED);

    drawCircle(74, 215, 8, RED);

    dda(105, 212, 74, 215, RED);
    dda(105, 218, 74, 215, RED);

    dda(130, 190, 130, 180, RED);
    dda(105, 180, 155, 180, RED);

    dda(110, 245, 150, 245, RED);
    dda(117, 238, 117, 245, RED);
    dda(143, 238, 143, 245, RED);
}

void drawTransformedHelicopter(Matrix M)
{
    Point p1, p2;

    p1 = transform({135, 215}, M);
    p2 = transform({155, 215}, M);
    dda(p1.x, p1.y, p2.x, p2.y, RED);

    p1 = transform({135, 215}, M);
    p2 = transform({135, 198}, M);
    dda(p1.x, p1.y, p2.x, p2.y, RED);

    p1 = transform({135, 198}, M);
    p2 = transform({147, 198}, M);
    dda(p1.x, p1.y, p2.x, p2.y, RED);

    p1 = transform({105, 212}, M);
    p2 = transform({74, 215}, M);
    dda(p1.x, p1.y, p2.x, p2.y, RED);

    p1 = transform({105, 218}, M);
    p2 = transform({74, 215}, M);
    dda(p1.x, p1.y, p2.x, p2.y, RED);

    p1 = transform({130, 190}, M);
    p2 = transform({130, 180}, M);
    dda(p1.x, p1.y, p2.x, p2.y, RED);

    p1 = transform({105, 180}, M);
    p2 = transform({155, 180}, M);
    dda(p1.x, p1.y, p2.x, p2.y, RED);

    p1 = transform({110, 245}, M);
    p2 = transform({150, 245}, M);
    dda(p1.x, p1.y, p2.x, p2.y, RED);

    p1 = transform({117, 238}, M);
    p2 = transform({117, 245}, M);
    dda(p1.x, p1.y, p2.x, p2.y, RED);

    p1 = transform({143, 238}, M);
    p2 = transform({143, 245}, M);
    dda(p1.x, p1.y, p2.x, p2.y, RED);

    Point body = transform({130, 215}, M);

    drawCircle(
        round(body.x),
        round(body.y),
        25,
        RED
    );

    Point back = transform({74, 215}, M);

    drawCircle(
        round(back.x),
        round(back.y),
        8,
        RED
    );
}

void drawObstacles()
{
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
}

int main()
{
    int choice;

    float tx = 0;
    float ty = 0;

    float sx = 1;
    float sy = 1;

    float angle = 0;

    cout << "\n===== TRANSFORMATION MENU =====";
    cout << "\n1. Translation";
    cout << "\n2. Scaling";
    cout << "\n3. Rotation";
    cout << "\n4. Composite Transformation";
    cout << "\n5. Exit";

    cout << "\n\nEnter choice: ";
    cin >> choice;

    Matrix M = identity();

    switch(choice)
    {
        case 1:

            cout << "\nEnter tx: ";
            cin >> tx;

            cout << "Enter ty: ";
            cin >> ty;

            M = translationMatrix(tx, ty);

            break;

        case 2:

            cout << "\nEnter sx: ";
            cin >> sx;

            cout << "Enter sy: ";
            cin >> sy;

            M = scalingMatrix(sx, sy);

            break;

        case 3:

            cout << "\nEnter angle: ";
            cin >> angle;

            M = rotationMatrix(angle);

            break;

        case 4:

            cout << "\nEnter tx: ";
            cin >> tx;

            cout << "Enter ty: ";
            cin >> ty;

            cout << "\nEnter sx: ";
            cin >> sx;

            cout << "Enter sy: ";
            cin >> sy;

            cout << "\nEnter angle: ";
            cin >> angle;

            M = translationMatrix(tx, ty);
            M = multiply(M, scalingMatrix(sx, sy));
            M = multiply(M, rotationMatrix(angle));

            break;

        case 5:
            return 0;

        default:

            cout << "\nInvalid choice!";
            return 0;
    }

    int gd = DETECT;
    int gm;

    char path[] = "";

    initgraph(&gd, &gm, path);

    cleardevice();

    drawObstacles();
    drawOriginalHelicopter();

    delay(3000);

    cleardevice();

    drawObstacles();
    drawTransformedHelicopter(M);

    getch();

    closegraph();

    return 0;
}

