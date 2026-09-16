#include <graphics.h>

int main()
{
    initwindow(800, 600, "Graphics Test");

    circle(400, 300, 100);
    line(100, 100, 700, 500);

    getch();
    closegraph();

    return 0;
}