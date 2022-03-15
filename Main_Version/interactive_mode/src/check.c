//#include "check.h"

int check_names(int PlayerNamber, struct Game *TempGame)
{
    if (PlayerNamber == 0)
    {
        return 0;
    }
    for (int i = 0; i < PlayerNamber; i++)
    {
        if (strcmp(TempGame->Player[i].Name, TempGame->Player[PlayerNamber].Name) == 0)
        {
            return 1;
        }
    }
    return 0;
}
int check_penguin(int CoordPengX, int CoordPengY, struct Game *TempGame)
{
    if (TempGame->Map[CoordPengX + 1][CoordPengY].Fish == 0 && TempGame->Map[CoordPengX][CoordPengY + 1].Fish == 0 && TempGame->Map[CoordPengX - 1][CoordPengY].Fish == 0 && TempGame->Map[CoordPengX][CoordPengY - 1].Fish == 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
void check_all_penguins(struct Game *TempGame)
{
    for (int i = 0; i < TempGame->NumPlayers; i++)
    {
        for (int u = 0; u < TempGame->NumPenguins; u++)
        {
            TempGame->Player[i].Penguin[u].Movable = check_penguin(TempGame->Player[i].Penguin[u].PositionX, TempGame->Player[i].Penguin[u].PositionY, TempGame);
        }
    }
}
int check_status(struct Game *TempGame)
{
    int x = 0;
    for (int i = 0; i < TempGame->NumPlayers; i++)
    {
        if (TempGame->Player[i].Movable == 1)
        {
            x++;
        }
    }
    if (x == TempGame->NumPlayers)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
int check_turn(int CoordPengX, int CoordPengY, int CoordTurnX, int CoordTurnY, struct Game *TempGame)
{
    if (CoordPengX == CoordTurnX)
    {
        if (CoordTurnY > CoordPengY)
        {
            for (int Y = CoordPengY + 1; Y <= CoordTurnY; Y++)
            {
                if (TempGame->Map[CoordPengX][Y].Fish == 0)
                {
                    return 1;
                }
            }
        }
        else if (CoordTurnY < CoordPengY)
        {
            for (int Y = CoordTurnY; Y < CoordPengY; Y++)
            {
                if (TempGame->Map[CoordPengX][Y].Fish == 0)
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
                if (TempGame->Map[X][CoordPengY].Fish == 0)
                {
                    return 1;
                }
            }
        }
        else if (CoordTurnX < CoordPengX)
        {
            for (int X = CoordTurnX; X < CoordPengX; X++)
            {
                if (TempGame->Map[X][CoordPengY].Fish == 0)
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
void check_all_players(struct Game *TempGame) 
{
    int x = 0;
    for (int i = 0; i < TempGame->NumPlayers; i++)
    {
        x = 0;
        for (int u = 0; u < TempGame->NumPenguins; u++)
        {
            x = x + TempGame->Player[i].Penguin[u].Movable;
        }
        if (x == TempGame->NumPenguins)
        {
            TempGame->Player[i].Movable = 1;
        }
    }
}