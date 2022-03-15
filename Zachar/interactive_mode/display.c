//#include "display.h"

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

                if (Game->Map[x][y].Penguin < 9)
                {
                    printf("%c %d", Game->Player[Game->Map[x][y].Player].NameUnit, Game->Map[x][y].Penguin + 1);
                }
                else
                {
                    printf("%c%d", Game->Player[Game->Map[x][y].Player].NameUnit, Game->Map[x][y].Penguin + 1);
                }
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
void sort_score(int NumPlayer, int *Score, int *PlayerScore)
{

    int x, y;
    for (int i = 0; i < NumPlayer; i++)
    {
        x = i;
        for (int u = i + 1; u < NumPlayer; u++)
        {
            if (Score[x] < Score[u])
            {
                x = u;
            }
        }
        y = Score[i];
        Score[i] = Score[x];
        Score[x] = y;
        y = PlayerScore[i];
        PlayerScore[i] = PlayerScore[x];
        PlayerScore[x] = y;
    }
}
void print_scoreboard(int *Score, int *PlayerScore, struct Game *Game)
{
    int Place = 1;
    for (int i = 0; i < Game->NumPlayers - 1; i++)
    {
        printf("The %d place: Player %s (%c) with score: %d\n", Place, Game->Player[PlayerScore[i]].Name, Game->Player[PlayerScore[i]].NameUnit, Score[i]);
        if (Score[i] != Score[i + 1])
        {
            Place = i + 2;
        }
    }
    printf("The %d place: Player %s (%c) with score: %d", Place, Game->Player[PlayerScore[Game->NumPlayers - 1]].Name, Game->Player[PlayerScore[Game->NumPlayers - 1]].NameUnit, Score[Game->NumPlayers - 1]);
}