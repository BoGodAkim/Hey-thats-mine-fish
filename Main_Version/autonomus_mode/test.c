#include <stdio.h>
#include <stdlib.h>
int main()
{
    int x = 0, y = 0, z = 0;
    system("gcc main.c -o main");
    system("gcc main2.c -o main2");
    for (int i = 0; i < 2; i++)
    {

        x = system("main.exe phase=placement penguins=2 board01.txt board01.txt");
        printf("\n");
        y = system("main2.exe phase=placement penguins=2 board01.txt board01.txt");
        
        printf("\n1:%d 2:%d\n",x,y);
    }
    while (x != 1 || y != 1)
    {
        x = system("main.exe phase=movement board01.txt board01.txt");
        printf("\n");
        y = system("main2.exe phase=movement board01.txt board01.txt");
        printf("\n1:%d 2:%d\n", x, y);
    }
}