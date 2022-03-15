
int check_penguin(int CoordPengX, int CoordPengY, struct Game *TempGame)
{
    if ((TempGame->Map[CoordPengX + 1][CoordPengY].Fish == 0 || TempGame->Map[CoordPengX + 1][CoordPengY].Player != -1) && (TempGame->Map[CoordPengX][CoordPengY + 1].Fish == 0 || TempGame->Map[CoordPengX][CoordPengY + 1].Player != -1) && (TempGame->Map[CoordPengX - 1][CoordPengY].Fish == 0 || TempGame->Map[CoordPengX - 1][CoordPengY].Player != -1) && (TempGame->Map[CoordPengX][CoordPengY - 1].Fish == 0 || TempGame->Map[CoordPengX][CoordPengY - 1].Player != -1))
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
        for (int u = 0; u < TempGame->Player[i].NumberOfPenguins; u++)
        {
            TempGame->Player[i].Penguin[u].Movable = check_penguin(TempGame->Player[i].Penguin[u].PositionX, TempGame->Player[i].Penguin[u].PositionY, TempGame);
        }
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
                if (TempGame->Map[CoordPengX][Y].Fish == 0 || TempGame->Map[CoordPengX][Y].Player != -1)
                {
                    return 1;
                }
            }
        }
        else if (CoordTurnY < CoordPengY)
        {
            for (int Y = CoordTurnY; Y < CoordPengY; Y++)
            {
                if (TempGame->Map[CoordPengX][Y].Fish == 0 || TempGame->Map[CoordPengX][Y].Player != -1)
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
                if (TempGame->Map[X][CoordPengY].Fish == 0 || TempGame->Map[X][CoordPengY].Player != -1)
                {
                    return 1;
                }
            }
        }
        else if (CoordTurnX < CoordPengX)
        {
            for (int X = CoordTurnX; X < CoordPengX; X++)
            {
                if (TempGame->Map[X][CoordPengY].Fish == 0 || TempGame->Map[X][CoordPengY].Player != -1)
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
    TempGame->Player[TempGame->Map[CoordPengX][CoordPengY].Player].Score = TempGame->Player[TempGame->Map[CoordPengX][CoordPengY].Player].Score + TempGame->Map[CoordTurnX][CoordTurnY].Fish;
    TempGame->Map[CoordPengX][CoordPengY].Fish = 0;
    TempGame->Map[CoordTurnX][CoordTurnY].Player = TempGame->Map[CoordPengX][CoordPengY].Player;
    TempGame->Map[CoordPengX][CoordPengY].Player = -1;
    return 0;
}
void check_all_players(struct Game *TempGame)
{
    int x = 0;
    for (int i = 0; i < TempGame->NumPlayers; i++)
    {
        x = 0;
        for (int u = 0; u < TempGame->Player[i].NumberOfPenguins; u++)
        {
            x = x + TempGame->Player[i].Penguin[u].Movable;
        }
        if (x == TempGame->Player[i].NumberOfPenguins)
        {
            TempGame->Player[i].Movable = 1;
        }
    }
}
void fill_data_about_penguins(struct Game *TempGame)
{
    for (int x = 1; x < TempGame->SizeMapX + 1; x++)
    {
        for (int y = 1; y < TempGame->SizeMapY + 1; y++)
        {
            if (TempGame->Map[x][y].Player != -1)
            {
                TempGame->Player[TempGame->Map[x][y].Player].Penguin[TempGame->Player[TempGame->Map[x][y].Player].NumberOfPenguins].PositionX = x;
                TempGame->Player[TempGame->Map[x][y].Player].Penguin[TempGame->Player[TempGame->Map[x][y].Player].NumberOfPenguins].PositionY = y;
                TempGame->Player[TempGame->Map[x][y].Player].NumberOfPenguins++;
            }
        }
    }
}
int find_my_number(struct Game *TempGame, char *Name)
{
    TempGame->MyNumber = -1;
    for (int i = 0; i < TempGame->NumPlayers; i++)
    {
        if (strcmp(TempGame->Player[i].Name, Name) == 0)
        {
            if (TempGame->MyNumber != -1)
            {
                return 1;
            }
            TempGame->MyNumber = i;
        }
    }
    return 0;
}
int check_game_with_cache(struct Game *TempGame, struct Game *Cache)
{
    if (TempGame->Phase < Cache->Phase)
    {
        return 6;
    }
    if (TempGame->SizeMapX != Cache->SizeMapX || TempGame->SizeMapY != Cache->SizeMapY || TempGame->MyNumber != Cache->MyNumber || TempGame->NumPenguins != Cache->NumPenguins || TempGame->NumPlayers != Cache->NumPlayers)
    {
        return 1;
    }
    for (int i = 0; i < TempGame->NumPlayers; i++)
    {
        if ((TempGame->Player[i].Movable != Cache->Player[i].Movable && Cache->Player[i].Movable == 1) || TempGame->Player[i].Score - Cache->Player[i].Score > 3 || TempGame->Player[i].Score - Cache->Player[i].Score < 0 || strcmp(TempGame->Player[i].Name, Cache->Player[i].Name) != 0)
        {
            return 7;
        }
        if (Cache->Phase == 0)
        {
            if (TempGame->Player[i].NumberOfPenguins - Cache->Player[i].NumberOfPenguins != 1 && TempGame->Player[i].NumberOfPenguins - Cache->Player[i].NumberOfPenguins != 0)
            {
                return 8;
            }
        }
        else
        {
            if (TempGame->Player[i].NumberOfPenguins != Cache->Player[i].NumberOfPenguins || TempGame->Player[i].NumberOfPenguins != Cache->NumPenguins)
            {
                return 9;
            }
        }
    }
    int XFrom, XTo, YFrom, YTo;
    for (int i = TempGame->MyNumber + 1; i != TempGame->MyNumber; i++)
    {
        if (i == TempGame->NumPlayers)
        {
            i = 0;
        }
        else
        {
            XFrom = 0;
            YFrom = 0;
            XTo = 0;
            YTo = 0;
            for (int x = 1; x < TempGame->SizeMapX + 1; x++)
            {
                for (int y = 1; y < TempGame->SizeMapY + 1; y++)
                {
                    if (TempGame->Map[x][y].Player == i && Cache->Map[x][y].Player == -1)
                    {
                        if (XTo == 0 && YTo == 0)
                        {
                            XTo = x;
                            YTo = y;
                        }
                        else
                        {
                            return 2;
                        }
                    }
                    if (TempGame->Map[x][y].Player == -1 && Cache->Map[x][y].Player == i)
                    {
                        if (XFrom == 0 && YFrom == 0)
                        {
                            XFrom = x;
                            YFrom = y;
                        }
                        else
                        {
                            return 2;
                        }
                    }
                }
            }
            if (Cache->Player[i].Movable == 1 && (XTo != 0 || YTo != 0))
            {
                return 5;
            }
            if (XTo == 0 && YTo == 0)
            {
                return 5;
            }
            if ((TempGame->Phase != Cache->Phase && i > TempGame->MyNumber) || (TempGame->Phase == Cache->Phase && TempGame->Phase == 0))
            {
                if (Cache->Map[XTo][YTo].Fish == 1)
                {
                    TempGame->Player[i].Score = TempGame->Player[i].Score + TempGame->Map[XTo][YTo].Fish;
                    TempGame->Map[XTo][YTo].Player = i;
                }
            }
            else
            {
                if (check_turn(XFrom, YFrom, XTo, YTo, Cache) == 1)
                {
                    return 3;
                }
            }
        }
    }
    for (int x = 1; x < TempGame->SizeMapX + 1; x++)
    {
        for (int y = 1; y < TempGame->SizeMapY + 1; y++)
        {
            if (TempGame->Map[x][y].Fish != Cache->Map[x][y].Fish && TempGame->Map[x][y].Player == -1) //(TempGame->Map[x][y].Fish != Cache->Map[x][y].Fish) //(TempGame->Map[x][y].Fish != Cache->Map[x][y].Fish && TempGame->Map[x][y].Player == -1)
            {
                return 4;
            }
        }
    }
    return 0;
}
int check_number_of_penguins(struct Game *TempGame)
{
    int MaxPenguins = TempGame->Player[0].NumberOfPenguins, MinPenguins = TempGame->Player[0].NumberOfPenguins;
    for (int i = 0; i < TempGame->NumPlayers; i++)
    {
        if (TempGame->Player[i].NumberOfPenguins > MaxPenguins)
        {
            return 1;
        }
        if (TempGame->Player[i].NumberOfPenguins < MaxPenguins)
        {
            if (MinPenguins == MaxPenguins && TempGame->Player[i].NumberOfPenguins + 1 == MaxPenguins && TempGame->Phase == 0)
            {
                MinPenguins = TempGame->Player[i].NumberOfPenguins;
            }
            else
            {
                return 1;
            }
        }
    }
}