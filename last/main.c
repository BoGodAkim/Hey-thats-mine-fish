#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "src/struct.h"
#include "src/mapgen.c"
#include "src/check.c"
#include "src/display.c"
#include "src/movement_phase.c"
#include "src/bot.c"
#include "src/placement_phase.c"

// 6 1 20 20 N R B 1 B 2 B 3 B 4 B 5 B 6
// 4 2 20 20 N R B 5 B 6 B 7 B 8
// 4 2 20 20 N R B 1 B 2 B 3 B 4
// 2 1 10 10 N R B 5 B 6
// 2 1 10 10 N R B 3 B 4
// 2 1 10 10 N R B 2 B 3
// 2 1 10 10 N R B 1 B 2
int main()
{
    srand(time(0));
    struct Game Game;
    printf("Enter number of players:");
    scanf("%d", &Game.NumPlayers);
    while (Game.NumPlayers <= 1)
    {
        printf("Invalid number of players.\nEnter correct number of players:");
        scanf("%d", &Game.NumPlayers);
    }
    printf("Enter number of penguins:");
    scanf("%d", &Game.NumPenguins);
    while (Game.NumPenguins <= 0)
    {
        printf("Invalid number of penguins.\nEnter correct number of penguins:");
        scanf("%d", &Game.NumPenguins);
    }
    printf("Enter size of the map:");
    scanf("%d%d", &Game.SizeMapX, &Game.SizeMapY);
    while (Game.SizeMapX <= 0 || Game.SizeMapY <= 0)
    {
        printf("Invalid size of the map.\nEnter correct size of the map:");
        scanf("%d%d", &Game.SizeMapX, &Game.SizeMapY);
    }
    while (Game.SizeMapX * Game.SizeMapY < Game.NumPlayers * Game.NumPenguins * 6)
    {
        printf("Map is small. Enter large size of the map:");
        scanf("%d%d", &Game.SizeMapX, &Game.SizeMapY);
        while (Game.SizeMapX <= 0 || Game.SizeMapY <= 0)
        {
            printf("Invalid size of the map.\nEnter correct size of the map:");
            scanf("%d%d", &Game.SizeMapX, &Game.SizeMapY);
        }
    }
    Game.Order = (int *)calloc(Game.NumPlayers, sizeof(int));
    Game.Map = (struct Map **)calloc(Game.SizeMapX+2, sizeof(struct Map *));
    for (int i = 0; i < Game.SizeMapX + 2; i++)
    {
        Game.Map[i] = (struct Map *)calloc(Game.SizeMapY + 2, sizeof(struct Map));
    }
    Game.Player = (struct Player *)calloc(Game.NumPlayers, sizeof(struct Player));
    for (int i = 0; i < Game.NumPlayers; i++)
    {
        Game.Player[i].Penguin = (struct Penguin *)calloc(Game.NumPenguins, sizeof(struct Penguin));
    }
    for (int x = 0; x < Game.SizeMapX + 2; x++)
    {
        for (int y = 0; y < Game.SizeMapY + 2; y++)
        {
            Game.Map[x][y].Penguin = -1;
            Game.Map[x][y].Player = -1;
        }
    }
    init_map(&Game);
    init_player_data(&Game);
    init_coord_peng(&Game);
    check_all_penguins(&Game);
    check_all_players(&Game);

    while (check_status(&Game) == 0)
    {
        for (int i = 0; i < Game.NumPlayers; i++)
        {
            if (Game.Player[Game.Order[i]].Movable == 0)
            {
                if (Game.Player[Game.Order[i]].Bot == 0)
                {
                    player_turn(Game.Order[i], &Game);
                }
                else
                {
                    bot_turn(Game.Order[i], &Game);
                }
                check_all_players(&Game);
            }
            else
            {
                printf("Player %s (%c), your penguins can't move. You skip turn.\n", Game.Player[Game.Order[i]].Name, Game.Player[Game.Order[i]].NameUnit);
            }
        }
    }
    int *Score, *PlayerScore;
    Score = (int *)calloc(Game.NumPlayers, sizeof(int));
    PlayerScore = (int *)calloc(Game.NumPlayers, sizeof(int));
    for (int i = 0; i < Game.NumPlayers; i++)
    {
        Score[i] = Game.Player[i].Score;
        PlayerScore[i] = i;
    }
    sort_score(Game.NumPlayers, Score, PlayerScore);
    print_scoreboard(Score, PlayerScore, &Game);
    free(Score);
    free(PlayerScore);
    free(Game.Order);
    for (int i = 0; i < Game.SizeMapX + 2; i++)
    {
        free(Game.Map[i]);
    }
    free(Game.Map);
    for (int i = 0; i < Game.NumPlayers; i++)
    {
        free(Game.Player[i].Penguin);
    }
    free(Game.Player);
    return 0;
}