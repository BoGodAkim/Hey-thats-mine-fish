// #include "functions.h"
// #include "struct.h"

void initData(GameData *Game)
{
    Game->Board = (Board **)calloc(Game->boardWidth + 2, sizeof(Board *));
    for (int i = 0; i < Game->boardWidth + 2; i++)
    {
        Game->Board[i] = (Board *)calloc(Game->boardHeight + 2, sizeof(Board));
    }
    Game->Player = (Player *)calloc(Game->playersCount, sizeof(Player));
    for (int i = 0; i < Game->playersCount; i++)
    {
        Game->Player[i].Penguin = (Penguin *)calloc(Game->penguinsCount, sizeof(Penguin));
    }
    for (int x = 0; x < Game->boardWidth + 2; x++)
    {
        for (int y = 0; y < Game->boardHeight + 2; y++)
        {
            Game->Board[x][y].Player = -1;
            Game->Board[x][y].Penguin = -1;
        }
    }
}

int check_names(int curPlayer, GameData *Game)
{
    for (int i = 0; i < curPlayer; i++)
    {
        if (strcmp(Game->Player[i].name, Game->Player[curPlayer].name) == 0)
        {
            return 1;
        }
    }
    return 0;
}

int check_penguin(int CoordX, int CoordY, GameData *Game)
{
    if (Game->Board[CoordX + 1][CoordY].Fish == 0 && Game->Board[CoordX][CoordY + 1].Fish == 0 && Game->Board[CoordX - 1][CoordY].Fish == 0 && Game->Board[CoordX][CoordY - 1].Fish == 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void check_all_penguins(GameData *Game)
{
    for (int i = 0; i < Game->playersCount; i++)
    {
        for (int u = 0; u < Game->penguinsCount; u++)
        {
            Game->Player[i].Penguin[u].canMove = check_penguin(Game->Player[i].Penguin[u].pos_X, Game->Player[i].Penguin[u].pos_Y, Game);
        }
    }
}

void check_all_players(GameData *Game)
{
    int x = 0;
    check_all_penguins(Game);
    for (int i = 0; i < Game->playersCount; i++)
    {
        x = 0;
        for (int u = 0; u < Game->penguinsCount; u++)
        {
            x += Game->Player[i].Penguin[u].canMove;
        }
        if (x == Game->penguinsCount)
        {
            Game->Player[i].haveMoves = 1;
        }
    }
}

int check_status(GameData *Game)
{
    int x = 0;
    check_all_players(Game);
    for (int i = 0; i < Game->playersCount; i++)
    {
        x += Game->Player[i].haveMoves;
    }
    if (x == Game->playersCount)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int check_turn(int CoordPengX, int CoordPengY, int CoordTurnX, int CoordTurnY, GameData *Game)
{
    if (CoordPengX == CoordTurnX)
    {
        if (CoordTurnY > CoordPengY)
        {
            for (int Y = CoordPengY + 1; Y <= CoordTurnY; Y++)
            {
                if (Game->Board[CoordPengX][Y].Fish == 0)
                {
                    return 1;
                }
            }
        }
        else if (CoordTurnY < CoordPengY)
        {
            for (int Y = CoordTurnY; Y < CoordPengY; Y++)
            {
                if (Game->Board[CoordPengX][Y].Fish == 0)
                {
                    return 1;
                }
            }
        }
        else
        {
            return 1;
        }
    }
    else if (CoordPengY == CoordTurnY)
    {
        if (CoordTurnX > CoordPengX)
        {
            for (int X = CoordPengX + 1; X <= CoordTurnX; X++)
            {
                if (Game->Board[X][CoordPengY].Fish == 0)
                {
                    return 1;
                }
            }
        }
        else if (CoordTurnX < CoordPengX)
        {
            for (int X = CoordTurnX; X < CoordPengX; X++)
            {
                if (Game->Board[X][CoordPengY].Fish == 0)
                {
                    return 1;
                }
            }
        }
        else
        {
            return 1;
        }
    }
    else
    {
        return 1;
    }
    return 0;
}

void print_map(GameData *Game)
{
    printf("\n    ");
    for (int x = 1; x <= Game->boardHeight; x++)
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
    for (int x = 1; x <= Game->boardWidth; x++)
    {
        printf("    ");
        for (int y = 1; y <= Game->boardHeight * 4; y++)
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
        for (int y = 1; y <= Game->boardHeight; y++)
        {
            printf("|");
            if (Game->Board[x][y].Player != -1)
            {
                if (Game->Board[x][y].Penguin < 9)
                {
                    printf("%d %d", Game->Board[x][y].Player + 1, Game->Board[x][y].Penguin + 1);
                }
                else
                {
                    printf("%d%d", Game->Board[x][y].Player, Game->Board[x][y].Penguin + 1);
                }
            }
            else
            {
                if (Game->Board[x][y].Fish != 0)
                {
                    printf(" %d ", Game->Board[x][y].Fish);
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

void sort_score(int playersCount, int *score, int *playerScore)
{

    int x, y;
    for (int i = 0; i < playersCount; i++)
    {
        x = i;
        for (int u = i + 1; u < playersCount; u++)
        {
            if (score[x] < score[u])
            {
                x = u;
            }
        }
        y = score[i];
        score[i] = score[x];
        score[x] = y;
        y = playerScore[i];
        playerScore[i] = playerScore[x];
        playerScore[x] = y;
    }
}

void print_scoreboard(int *score, int *playerScore, GameData *Game)
{
    int Place = 1;
    for (int i = 0; i < Game->playersCount - 1; i++)
    {
        printf("The %d place: Player %s with score: %d\n", Place, Game->Player[playerScore[i]].name, score[i]);
        if (score[i] != score[i + 1])
        {
            Place = i + 2;
        }
    }
    printf("The %d place: Player %s with score: %d", Place, Game->Player[playerScore[Game->playersCount - 1]].name, score[Game->playersCount - 1]);
}