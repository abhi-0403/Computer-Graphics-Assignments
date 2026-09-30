#include <iostream>
#include <graphics.h>
#include <cmath>
#include <iomanip>

using namespace std;

struct Point
{
    float x, y;
};

void printMatrix(float m[3][3], const string &name)
{
    cout << "\n" << name << " Matrix:\n";
    for (int i = 0; i < 3; i++)
    {
        cout << "[ ";
        for (int j = 0; j < 3; j++)
        {
            cout << setw(8) << fixed << setprecision(2) << m[i][j] << " ";
        }
        cout << "]\n";
    }
}

void multiplyMatrix(float A[3][3], float B[3][3], float Result[3][3])
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            Result[i][j] = 0;
            for (int k = 0; k < 3; k++)
            {
                Result[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

void applyTransformation(float M[3][3], Point p[], int n)
{
    for (int i = 0; i < n; i++)
    {
        float oldX = p[i].x;
        float oldY = p[i].y;

        p[i].x = M[0][0] * oldX + M[0][1] * oldY + M[0][2] * 1.0f;
        p[i].y = M[1][0] * oldX + M[1][1] * oldY + M[1][2] * 1.0f;
    }
}

void getTranslationMatrix(float tx, float ty, float T[3][3])
{
    float mat[3][3] = 
    {
        { 1,  0, tx },
        { 0,  1, ty },
        { 0,  0,  1 }
    };

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            T[i][j] = mat[i][j];
        }
    }
}

void getScalingMatrix(float sx, float sy, float S[3][3])
{
    float mat[3][3] = 
    {
        { sx,  0,  0 },
        {  0, sy,  0 },
        {  0,  0,  1 }
    };

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            S[i][j] = mat[i][j];
        }
    }
}

void getRotationMatrix(float angle, float R[3][3])
{
    float rad = angle * 3.14159f / 180.0f;
    float mat[3][3] = 
    {
        { cos(rad), -sin(rad), 0 },
        { sin(rad),  cos(rad), 0 },
        {        0,         0, 1 }
    };

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            R[i][j] = mat[i][j];
        }
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

    for (int i = 0; i <= steps; i++)
    {
        putpixel(round(x), round(y), color);
        x += xinc;
        y += yinc;
    }
}

void draw(Point p[], int n, int color)
{
    for (int i = 0; i < n; i++)
    {
        int j = (i + 1) % n;
        dda(p[i].x, p[i].y, p[j].x, p[j].y, color);
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
    for (int i = 0; i < n; i++)
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

    float finalMatrix[3][3] = 
    {
        { 1, 0, 0 },
        { 0, 1, 0 },
        { 0, 0, 1 }
    };

    if (choice == 1)
    {
        float tx, ty;
        cout << "Enter tx: ";
        cin >> tx;
        cout << "Enter ty: ";
        cin >> ty;

        getTranslationMatrix(tx, ty, finalMatrix);
        printMatrix(finalMatrix, "Translation");
    }
    else if (choice == 2)
    {
        float sx, sy;
        cout << "Enter sx: ";
        cin >> sx;
        cout << "Enter sy: ";
        cin >> sy;

        getScalingMatrix(sx, sy, finalMatrix);
        printMatrix(finalMatrix, "Scaling");
    }
    else if (choice == 3)
    {
        float angle;
        cout << "Enter angle: ";
        cin >> angle;

        getRotationMatrix(angle, finalMatrix);
        printMatrix(finalMatrix, "Rotation");
    }
    else if (choice == 4)
    {
        float tx, ty, sx, sy, angle;

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

        float T[3][3];
        float S[3][3];
        float R[3][3];

        getTranslationMatrix(tx, ty, T);
        getScalingMatrix(sx, sy, S);
        getRotationMatrix(angle, R);

        printMatrix(T, "Translation (T)");
        printMatrix(S, "Scaling (S)");
        printMatrix(R, "Rotation (R)");

        float ST[3][3];
        multiplyMatrix(S, T, ST);
        multiplyMatrix(R, ST, finalMatrix);

        printMatrix(finalMatrix, "Composite (R * S * T)");
    }
    else
    {
        cout << "Invalid choice!\n";
        return 0;
    }

    applyTransformation(finalMatrix, result, n);

    cout << "\nTransformed Coordinates:\n";
    for (int i = 0; i < n; i++)
    {
        cout << "(" << result[i].x << ", " << result[i].y << ")\n";
    }

    int gd = DETECT;
    int gm;

    initgraph(&gd, &gm, (char*)"");

    draw(original, n, WHITE);
    draw(result, n, WHITE);

    getch();
    closegraph();

    return 0;
}