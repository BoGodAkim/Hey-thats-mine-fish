#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "src/struct.h"
#include "src/work_file.c"
#include "src/check.c"
#include "src/bot.c"
// TODO:Rewrite reading file with cheking input data;
// TODO:Rewrite logic of compairing potential;
void print_map(struct Game *TempGame)
{
    printf("\n    ");
    for (int x = 1; x <= TempGame->SizeMapY; x++)
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
    for (int x = 1; x <= TempGame->SizeMapX; x++)
    {
        printf("    ");
        for (int y = 1; y <= TempGame->SizeMapY * 4; y++)
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
        for (int y = 1; y <= TempGame->SizeMapY; y++)
        {
            printf("|");
            if (TempGame->Map[x][y].Player != -1)
            {
                printf("PL%d", TempGame->Map[x][y].Player);
            }
            else
            {
                if (TempGame->Map[x][y].Fish != 0)
                {
                    printf(" %d ", TempGame->Map[x][y].Fish);
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
    char *ReadFile, *WriteFile, CacheFile[200], NameCache[] = {'M','o','s','a','d','\0'}; // NameCache[] = "BoGodAkim";
    struct Game Game;
    struct Game GameCache;
    Game.Phase = -1;
    Game.NumPenguins = 0;
    Game.NumPlayers = 0;
    if (argc == 2 && strcmp(argv[1], "name"))
    {
        printf("%s", NameCache);
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
    if (find_my_number(&Game, NameCache) == 1)
    {
        printf("Two players with my ID");
        return 2;
    }
    if (Game.MyNumber == -1 && Game.Phase == 1)
    {
        printf("Don't have player with my ID");
        return 2;
    }
    if (Game.MyNumber == -1)
    {
        Game.Player = (struct Player *)realloc(Game.Player, Game.NumPlayers + 1);
        Game.Player[Game.NumPlayers].Name = (char *)calloc(strlen(NameCache) + 1, sizeof(char));
        for (int i = 0; i < strlen(NameCache); i++)
        {
            Game.Player[Game.NumPlayers].Name[i] = NameCache[i];
        }
        Game.Player[Game.NumPlayers].Name[strlen(NameCache)] = 0;
        printf("\n%s %d %s\n", NameCache, strlen(NameCache), Game.Player[Game.NumPlayers].Name);
        Game.Player[Game.NumPlayers].Score = 0;
        Game.Player[Game.NumPlayers].Movable = 0;
        Game.Player[Game.NumPlayers].NumberOfPenguins = 0;
        Game.MyNumber = Game.NumPlayers;
        Game.NumPlayers++;
    }
    // print_map(&Game);
    fill_data_about_penguins(&Game);
    check_all_penguins(&Game);
    check_all_players(&Game);
    if (Game.Phase == 1)
    {
        Game.NumPenguins = Game.Player[0].NumberOfPenguins;
    }
    // if (check_number_of_penguins(&Game) == 1)
    // {
    //     return 2;
    // }
    if (read_game_cache(&GameCache, NameCache) == 0)
    {
        printf("\nErorr:%d\n", check_game_with_cache(&Game, &GameCache));
    }
    if (Game.Phase == 0)
    {
        if (Game.NumPenguins > Game.Player[Game.MyNumber].NumberOfPenguins)
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
        if (Game.Player[Game.MyNumber].Movable == 0)
        {
            bot_make_turn(&Game);
        }
        else
        {
            write_game_cache(&Game, NameCache);
            printf("My Player can't take move.");
            return 1;
        }
    }
    printf("\n%s %d %s\n", NameCache, strlen(NameCache), Game.Player[Game.MyNumber].Name);
    write_game_cache(&Game, NameCache);
    // print_map(&Game);
    write_game(&Game, WriteFile);
    return 0;
}