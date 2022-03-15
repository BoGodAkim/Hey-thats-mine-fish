#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <windows.h>
#include "src/struct.h"
#include "src/functions.c"
#include "src/mapgen.c"

int main()
{
    srand(time(NULL));
    GameData Game;
    printf("\033[2J\033[1;1H");

    do
    {
        printf("Please enter an amount of players: ");
        scanf("%d", &Game.playersCount);
        if (40 < Game.playersCount || Game.playersCount <= 1)
        {
            printf("\033[2J\033[1;1H");
            printf("ERROR: Please enter a number larger than 1 and lower 40\n");
        }
    } while (40 < Game.playersCount || Game.playersCount <= 1);

    printf("\033[2J\033[1;1H");

    do
    {
        printf("Please enter an amount of penguins for each player: ");
        scanf("%d", &Game.penguinsCount);
        if (40 < Game.penguinsCount || Game.penguinsCount <= 0)
        {
            printf("\033[2J\033[1;1H");
            printf("ERROR: Please enter a number larger than 0 and lower 40\n");
        }
    } while (40 < Game.penguinsCount || Game.penguinsCount <= 0);

    printf("\033[2J\033[1;1H");

    do
    {
        printf("Please enter preferred dimensions of a map: ");
        scanf("%d%d", &Game.boardHeight, &Game.boardWidth);
        if (Game.boardHeight * Game.boardWidth < Game.playersCount * Game.penguinsCount * 4 || Game.boardHeight > 100 || Game.boardWidth > 100)
        {
            printf("\033[2J\033[1;1H");
            printf("ERROR: Please enter different map dimensions\n");
        }
    } while (Game.boardHeight * Game.boardWidth < Game.playersCount * Game.penguinsCount * 4 || Game.boardHeight > 100 || Game.boardWidth > 100);

    initData(&Game);

    while (generate_map(&Game) < Game.playersCount * Game.penguinsCount)
    {
    }

    printf("\033[2J\033[1;1H");
    print_map(&Game);
    Sleep(3000);

    for (int i = 0; i < Game.playersCount; i++)
    {
        printf("\033[2J\033[1;1H");
        printf("Player %d enter nickname:", i + 1);
        scanf("%s", &Game.Player[i].name);
        while (check_names(i, &Game) == 1)
        {
            printf("\033[2J\033[1;1H");
            printf("ERROR: This nickname is taken\n");
            printf("Player %d enter nickname:", i + 1);
            scanf("%s", &Game.Player[i].name);
        }
    }

    for (int i = 0; i < Game.penguinsCount; i++)
    {
        for (int o = 0; o < Game.playersCount; o++)
        {
            int X = 0, Y = 0;
            printf("\033[2J\033[1;1H");
            print_map(&Game);
            printf("%s, enter coordinate with 1 fish for %d penguin:", Game.Player[o].name, i + 1);
            scanf("%d %d", &X, &Y);
            while (X < 1 || Y < 1 || X > Game.boardWidth || Y > Game.boardHeight || Game.Board[X][Y].Fish != 1)
            {
                printf("\033[2J\033[1;1H");
                print_map(&Game);
                printf("ERROR: Incorrect coordinate\n");
                printf("%s, enter coordinate with 1 fish for %d penguin:", Game.Player[o].name, i + 1);
                scanf("%d %d", &X, &Y);
            }
            Game.Player[o].Penguin[i].pos_X = X;
            Game.Player[o].Penguin[i].pos_Y = Y;
            Game.Player[o].score += 1;
            Game.Board[X][Y].Fish = 0;
            Game.Board[X][Y].Player = o;
            Game.Board[X][Y].Penguin = i;
        }
    }

    int curPlayer = 0;

    while (check_status(&Game) == 0)
    {
        if (curPlayer == Game.playersCount)
        {
            curPlayer = 0;
        }
        if (Game.Player[curPlayer].haveMoves == 0)
        {
            printf("\033[2J\033[1;1H");
            print_map(&Game);
            int curPenguin = 0, X = 0, Y = 0;
            printf("%s, choose penguin which you want to move(from 1 to %i):", Game.Player[curPlayer].name, Game.penguinsCount);
            scanf("%d", &curPenguin);
            curPenguin--;
            while (curPenguin < 0 || curPenguin >= Game.penguinsCount || Game.Player[curPlayer].Penguin[curPenguin].canMove == 1)
            {
                printf("\033[2J\033[1;1H");
                print_map(&Game);
                printf("ERROR: Incorrect number of penguin\n");
                printf("%s, choose penguin which you want to move(from 1 to %i):", Game.Player[curPlayer].name, Game.penguinsCount);
                scanf("%d", &curPenguin);
                curPenguin--;
            }
            printf("\033[2J\033[1;1H");
            print_map(&Game);
            printf("%s, enter coordinates in which do you want move:", Game.Player[curPlayer].name);
            scanf("%d%d", &X, &Y);
            while (X < 1 || Y < 1 || X > Game.boardWidth || Y > Game.boardHeight || check_turn(Game.Player[curPlayer].Penguin[curPenguin].pos_X, Game.Player[curPlayer].Penguin[curPenguin].pos_Y, X, Y, &Game) == 1)
            {
                printf("\033[2J\033[1;1H");
                print_map(&Game);
                printf("ERROR: Incorrect coordinates\n");
                printf("%s, enter coordinates in which do you want move:", Game.Player[curPlayer].name);
                scanf("%d%d", &X, &Y);
            }
            Game.Board[Game.Player[curPlayer].Penguin[curPenguin].pos_X][Game.Player[curPlayer].Penguin[curPenguin].pos_Y].Player = -1;
            Game.Board[Game.Player[curPlayer].Penguin[curPenguin].pos_X][Game.Player[curPlayer].Penguin[curPenguin].pos_Y].Penguin = -1;
            Game.Player[curPlayer].Penguin[curPenguin].pos_X = X;
            Game.Player[curPlayer].Penguin[curPenguin].pos_Y = Y;
            Game.Player[curPlayer].score += Game.Board[X][Y].Fish;
            Game.Board[X][Y].Fish = 0;
            Game.Board[X][Y].Player = curPlayer;
            Game.Board[X][Y].Penguin = curPenguin;
        }
        else
        {
            printf("\033[2J\033[1;1H");
            print_map(&Game);
            printf("%s, you can't move.\n", Game.Player[curPlayer].name);
            Sleep(5000);
        }
        curPlayer++;
    }

    int *score, *playerScore;
    score = (int *)calloc(Game.playersCount, sizeof(int));
    playerScore = (int *)calloc(Game.playersCount, sizeof(int));
    for (int i = 0; i < Game.playersCount; i++)
    {
        score[i] = Game.Player[i].score;
        playerScore[i] = i;
    }
    printf("\033[2J\033[1;1H");
    sort_score(Game.playersCount, score, playerScore);
    print_scoreboard(score, playerScore, &Game);
}
