#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
int main()
{
    int x = 0, y = 0;
    FILE *input, *output;
    char buffer[BUFSIZ];
    size_t nread;
    input = fopen("board/board02.txt", "rb");
    output = fopen("board.txt", "wb");
    while (nread = fread(buffer, sizeof(char), sizeof(buffer), input))
    {
        fwrite(buffer, sizeof(char), nread, output);
    }
    fclose(input);
    fclose(output);
    system("gcc main.c -o main");
    system("gcc main2.c -o main2");
    for (int i = 0; i < 2; i++)
    {

        x = system("main.exe phase=placement penguins=2 board.txt board.txt");
        printf("\n");
        // Sleep(3000);
        y = system("main2.exe phase=placement penguins=2 board.txt board.txt");
        printf("\n1:%d 2:%d\n", x, y);
        // Sleep(3000);
    }
    while (x != 1 || y != 1)
    {
        x = system("main.exe phase=movement board.txt board.txt");
        printf("\n");
        // Sleep(3000);
        y = system("main2.exe phase=movement board.txt board.txt");
        printf("\n1:%d 2:%d\n", x, y);
        // Sleep(3000);
    }
}