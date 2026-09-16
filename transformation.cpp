#include <iostream>
#include <graphics.h>
#include <cmath>

using namespace std;

struct Point
{
    float x, y;
};



void translation(Point p[], int n, float tx, float ty)
{
    for(int i = 0; i < n; i++)
    {
        p[i].x = p[i].x + tx;
        p[i].y = p[i].y + ty;
    }
}



void scaling(Point p[], int n, float sx, float sy)
{
    for(int i = 0; i < n; i++)
    {
        p[i].x = p[i].x * sx;
        p[i].y = p[i].y * sy;
    }
}



void rotation(Point p[], int n, float angle)
{
    float rad = angle * 3.14159 / 180;

    for(int i = 0; i < n; i++)
    {
        float x = p[i].x;
        float y = p[i].y;

        p[i].x = x * cos(rad) - y * sin(rad);
        p[i].y = x * sin(rad) + y * cos(rad);
    }
}



void dda(float x1, float y1, float x2, float y2, int color)
{
    float dx = x2 - x1;
    float dy = y2 - y1;

    float steps = max(abs(dx), abs(dy));

    float xinc = dx / steps;
    float yinc = dy / steps;

    float x = x1;
    float y = y1;

    for(int i = 0; i <= steps; i++)
    {
        putpixel(round(x), round(y), color);

        x = x + xinc;
        y = y + yinc;
    }
}



void draw(Point p[], int n, int color)
{
    for(int i = 0; i < n; i++)
    {
        int j = (i + 1) % n;

        dda(p[i].x, p[i].y,p[j].x, p[j].y, color);
    }
}


int main()
{
    int n;

    cout << "Enter number of points: ";
    cin >> n;

    Point original[20];
    Point result[20];

    cout << "Enter coordinates:\n";

    for(int i = 0; i < n; i++)
    {
        cout << "Point " << i + 1 << ": ";
        cin >> original[i].x >> original[i].y;

        result[i] = original[i];
    }


    int choice;

    cout << "\n1. Translation";
    cout << "\n2. Scaling";
    cout << "\n3. Rotation";
    cout << "\n4. Composite Transformation";

    cout << "\nEnter choice: ";
    cin >> choice;


    float tx, ty;
    float sx, sy;
    float angle;


    switch(choice)
    {
        case 1:

            cout << "Enter tx: ";
            cin >> tx;

            cout << "Enter ty: ";
            cin >> ty;

            translation(result, n, tx, ty);

            break;


        case 2:

            cout << "Enter sx: ";
            cin >> sx;

            cout << "Enter sy: ";
            cin >> sy;

            scaling(result, n, sx, sy);

            break;


        case 3:

            cout << "Enter angle: ";
            cin >> angle;

            rotation(result, n, angle);

            break;


        case 4:

            cout << "Enter tx: ";
            cin >> tx;

            cout << "Enter ty: ";
            cin >> ty;

            cout << "Enter sx: ";
            cin >> sx;

            cout << "Enter sy: ";
            cin >> sy;

            cout << "Enter angle: ";
            cin >> angle;

            translation(result, n, tx, ty);
            scaling(result, n, sx, sy);
            rotation(result, n, angle);

            break;


        default:

            cout << "Invalid choice!";
            return 0;
    }


    cout << "\nTransformed Coordinates:\n";

    for(int i = 0; i < n; i++)
    {
        cout << "("
             << result[i].x
             << ", "
             << result[i].y
             << ")\n";
    }


    int gd = DETECT;
    int gm;

    initgraph(&gd, &gm, (char*)"");



    draw(original, n, BLUE);


    draw(result, n, RED);


    getch();

    closegraph();

    return 0;
}

