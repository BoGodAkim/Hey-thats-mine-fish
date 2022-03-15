//#include "check.h"

int check_names(int PlayerNamber, struct Game *Game)
{
    if (PlayerNamber == 0)
    {
        return 0;
    }
    for (int i = 0; i < PlayerNamber; i++)
    {
        if (strcmp(Game->Player[i].Name, Game->Player[PlayerNamber].Name) == 0)
        {
            return 1;
        }
    }
    return 0;
}
int check_penguin(int CoordPengX, int CoordPengY, struct Game *Game)
{
    if (Game->Map[CoordPengX + 1][CoordPengY].Fish == 0 && Game->Map[CoordPengX][CoordPengY + 1].Fish == 0 && Game->Map[CoordPengX - 1][CoordPengY].Fish == 0 && Game->Map[CoordPengX][CoordPengY - 1].Fish == 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
void check_all_penguins(struct Game *Game)
{
    for (int i = 0; i < Game->NumPlayers; i++)
    {
        for (int u = 0; u < Game->NumPenguins; u++)
        {
            Game->Player[i].Penguin[u].Movable = check_penguin(Game->Player[i].Penguin[u].PositionX, Game->Player[i].Penguin[u].PositionY, Game);
        }
    }
}
int check_status(struct Game *Game)
{
    int x = 0;
    for (int i = 0; i < Game->NumPlayers; i++)
    {
        if (Game->Player[i].Movable == 1)
        {
            x++;
        }
    }
    if (x == Game->NumPlayers)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
int check_turn(int CoordPengX, int CoordPengY, int CoordTurnX, int CoordTurnY, struct Game *Game)
{
    if (CoordPengX == CoordTurnX)
    {
        if (CoordTurnY > CoordPengY)
        {
            for (int Y = CoordPengY + 1; Y <= CoordTurnY; Y++)
            {
                if (Game->Map[CoordPengX][Y].Fish == 0)
                {
                    return 1;
                }
            }
        }
        else if (CoordTurnY < CoordPengY)
        {
            for (int Y = CoordTurnY; Y < CoordPengY; Y++)
            {
                if (Game->Map[CoordPengX][Y].Fish == 0)
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
                if (Game->Map[X][CoordPengY].Fish == 0)
                {
                    return 1;
                }
            }
        }
        else if (CoordTurnX < CoordPengX)
        {
            for (int X = CoordTurnX; X < CoordPengX; X++)
            {
                if (Game->Map[X][CoordPengY].Fish == 0)
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
void check_all_players(struct Game *Game)
{
    int x = 0;
    for (int i = 0; i < Game->NumPlayers; i++)
    {
        x = 0;
        for (int u = 0; u < Game->NumPenguins; u++)
        {
            x = x + Game->Player[i].Penguin[u].Movable;
        }
        if (x == Game->NumPenguins)
        {
            Game->Player[i].Movable = 1;
        }
    }
}