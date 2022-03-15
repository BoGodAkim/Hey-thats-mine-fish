//#include "display.h"

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
                if (TempGame->Player[TempGame->Map[x][y].Player].Bot == 0)
                {
                    if (TempGame->Map[x][y].Penguin < 9)
                    {
                        printf(" ");
                    }
                    printf("%c%d", TempGame->Player[TempGame->Map[x][y].Player].NameUnit, TempGame->Map[x][y].Penguin + 1);
                }
                else{
                    if (TempGame->Player[TempGame->Map[x][y].Player].BotNumber < 10)
                    {
                        printf(" ");
                    }
                    printf("%c%d", TempGame->Player[TempGame->Map[x][y].Player].NameUnit, TempGame->Player[TempGame->Map[x][y].Player].BotNumber);
                }
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
void sort_score(int TempNumPlayer, int *TempScore, int *TempPlayerScore)
{

    int x, y;
    for (int i = 0; i < TempNumPlayer; i++)
    {
        x = i;
        for (int u = i + 1; u < TempNumPlayer; u++)
        {
            if (TempScore[x] < TempScore[u])
            {
                x = u;
            }
        }
        y = TempScore[i];
        TempScore[i] = TempScore[x];
        TempScore[x] = y;
        y = TempPlayerScore[i];
        TempPlayerScore[i] = TempPlayerScore[x];
        TempPlayerScore[x] = y;
    }
}
void print_scoreboard(int *TempScore, int *TempPlayerScore, struct Game *TempGame)
{
    int Place = 1;
    for (int i = 0; i < TempGame->NumPlayers - 1; i++)
    {
        printf("The %d place: Player %s (%c) with score: %d\n", Place, TempGame->Player[TempPlayerScore[i]].Name, TempGame->Player[TempPlayerScore[i]].NameUnit, TempScore[i]);
        if (TempScore[i] != TempScore[i + 1])
        {
            Place = i + 2;
        }
    }
    printf("The %d place: Player %s (%c) with score: %d", Place, TempGame->Player[TempPlayerScore[TempGame->NumPlayers - 1]].Name, TempGame->Player[TempPlayerScore[TempGame->NumPlayers - 1]].NameUnit, TempScore[TempGame->NumPlayers - 1]);
}
