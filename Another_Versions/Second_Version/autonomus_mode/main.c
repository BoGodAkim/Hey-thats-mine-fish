#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "struct.h"
#include "work_file.c"
#include "check.c"
#include "bot.c"

void print_map(struct Game *Game)
{
    printf("\n    ");
    for (int x = 1; x <= Game->SizeMapY; x++)
    {
        printf("|");
        if (x < 100)
        {
            printf(" ");
        }
        if (x < 10)
        {
            printf("0");
        }
        printf("%d", x);
    }
    printf("\n\n");
    for (int x = 1; x <= Game->SizeMapX; x++)
    {
        printf("    ");
        for (int y = 1; y <= Game->SizeMapY * 4; y++)
        {
            printf("_");
        }
        printf("\n");
        if (x < 100)
        {
            printf(" ");
        }
        if (x < 10)
        {
            printf("0");
        }
        printf("%d ", x);
        for (int y = 1; y <= Game->SizeMapY; y++)
        {
            printf("|");
            if (Game->Map[x][y].Player != -1)
            {
                printf("PL%d", Game->Map[x][y].Player);
            }
            else
            {
                if (Game->Map[x][y].Fish != 0)
                {
                    printf(" %d ", Game->Map[x][y].Fish);
                }
                else
                {
                    printf("   ");
                }
            }
        }
        printf("\n");
    }
}
int main(int argc, char *argv[])
{
    char *ReadFile, *WriteFile, CacheFile[200], MyName[] = {'M', 'o', 's', 'a', 'd', 0}; // MyName[] = "BoGodAkim";
    struct Game Game;
    Game.Phase = -1;
    Game.NumPenguins = 0;
    Game.NumPlayers = 0;
    if (argc == 2 && strcmp(argv[1], "name"))
    {
        printf("%s", MyName);
        return 0;
    }
    if (argc != 5 && argc != 4)
    {
        printf("Incorrect parametr");
        return 3;
    }
    if (strcmp(argv[1], "phase=placement") == 0)
    {
        Game.Phase = 0;
        if (strncmp(argv[2], "penguins=", 9) != 0)
        {
            printf("Incorrect parametr");
            return 3;
        }
        for (int i = 9; i < strlen(argv[2]); i++)
        {
            Game.NumPenguins = Game.NumPenguins * 10 + argv[2][i] - '0';
        }
        ReadFile = argv[3];
        WriteFile = argv[4];
    }
    if (strcmp(argv[1], "phase=movement") == 0)
    {
        Game.Phase = 1;
        ReadFile = argv[2];
        WriteFile = argv[3];
    }
    if (Game.Phase == -1)
    {
        printf("Incorrect parametr");
        return 3;
    }
    if (read_game(&Game, ReadFile) == 1)
    {
        printf("Can't open file");
        return 3;
    }
    if (find_my_number(&Game, MyName) == 1)
    {
        printf("Two players with my ID");
        return 2;
    }
    if (Game.MyNumber == -1 && Game.Phase == 1)
    {
        printf("Don't have player with my ID");
        return 2;
    }
    fill_data_about_penguins(&Game);
    //print_map(&Game);
    if (Game.Phase == 0)
    {
        if (Game.MyNumber == -1 || Game.NumPenguins > Game.Player[Game.MyNumber].NumberOfPenguins)
        {
            if (bot_put_penguin(&Game) == 1)
            {
                printf("Don't have cells with 1 fish.");
                return 2;
            }
        }
        else
        {
            printf("My Player can't put penguin, because put before all penguins.");
            return 2;
        }
    }
    else
    {
        check_all_penguins(&Game);
        check_all_players(&Game);
        Game.NumPenguins = Game.Player[0].NumberOfPenguins;
        if (Game.Player[Game.MyNumber].Movable == 0)
        {
            bot_make_turn(&Game);
        }
        else
        {
            printf("My Player can't take move.");
            return 1;
        }
    }
    // print_map(&Game);
    write_game(&Game, WriteFile);
    if (Game.MyNumber == -1)
    {
        add_my_name(&Game, WriteFile, MyName);
    }
    return 0;
}