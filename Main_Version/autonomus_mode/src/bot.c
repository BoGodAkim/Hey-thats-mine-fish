int choose_penguins(int *ListOfPenguins, struct Game *TempGame)
{
    int NumberOfSide, CounterOfPenguins = 0;
    for (int i = 0; i < TempGame->Player[TempGame->MyNumber].NumberOfPenguins; i++)
    {
        NumberOfSide = 4;
        if (TempGame->Map[TempGame->Player[TempGame->MyNumber].Penguin[i].PositionX + 1][TempGame->Player[TempGame->MyNumber].Penguin[i].PositionY].Fish == 0 || TempGame->Map[TempGame->Player[TempGame->MyNumber].Penguin[i].PositionX + 1][TempGame->Player[TempGame->MyNumber].Penguin[i].PositionY].Player != -1)
        {
            NumberOfSide--;
        }
        if (TempGame->Map[TempGame->Player[TempGame->MyNumber].Penguin[i].PositionX - 1][TempGame->Player[TempGame->MyNumber].Penguin[i].PositionY].Fish == 0 || TempGame->Map[TempGame->Player[TempGame->MyNumber].Penguin[i].PositionX - 1][TempGame->Player[TempGame->MyNumber].Penguin[i].PositionY].Player != -1)
        {
            NumberOfSide--;
        }
        if (TempGame->Map[TempGame->Player[TempGame->MyNumber].Penguin[i].PositionX][TempGame->Player[TempGame->MyNumber].Penguin[i].PositionY + 1].Fish == 0 || TempGame->Map[TempGame->Player[TempGame->MyNumber].Penguin[i].PositionX][TempGame->Player[TempGame->MyNumber].Penguin[i].PositionY + 1].Player != -1)
        {
            NumberOfSide--;
        }
        if (TempGame->Map[TempGame->Player[TempGame->MyNumber].Penguin[i].PositionX][TempGame->Player[TempGame->MyNumber].Penguin[i].PositionY - 1].Fish == 0 || TempGame->Map[TempGame->Player[TempGame->MyNumber].Penguin[i].PositionX][TempGame->Player[TempGame->MyNumber].Penguin[i].PositionY - 1].Player != -1)
        {
            NumberOfSide--;
        }
        if (NumberOfSide == 1)
        {
            ListOfPenguins[CounterOfPenguins] = i;
            CounterOfPenguins++;
        }
    }
    if (CounterOfPenguins == 0)
    {
        for (int i = 0; i < TempGame->Player[TempGame->MyNumber].NumberOfPenguins; i++)
        {
            if (TempGame->Player[TempGame->MyNumber].Penguin[i].Movable == 0)
            {
                ListOfPenguins[CounterOfPenguins] = i;
                CounterOfPenguins++;
            }
        }
    }
    return CounterOfPenguins;
}
int count_direction(int x, int y, struct Game *TempGame)
{
    int Counter = 0;
    if (TempGame->Map[x][y - 1].Fish != 0 && TempGame->Map[x][y - 1].Player == -1)
    {
        Counter++;
    }
    if (TempGame->Map[x][y + 1].Fish != 0 && TempGame->Map[x][y + 1].Player == -1)
    {
        Counter++;
    }
    if (TempGame->Map[x + 1][y].Fish != 0 && TempGame->Map[x + 1][y].Player == -1)
    {
        Counter++;
    }
    if (TempGame->Map[x - 1][y].Fish != 0 && TempGame->Map[x - 1][y].Player == -1)
    {
        Counter++;
    }
    return Counter;
}
void count_potential(int *Potential, int X, int Y, struct Game *TempGame)
{
    Potential[4] = 0;
    Potential[3] = 0;
    Potential[2] = 0;
    int TempNumber = 1;
    while (TempGame->Map[X + TempNumber][Y].Fish != 0 && TempGame->Map[X + TempNumber][Y].Player == -1)
    {
        Potential[TempGame->Map[X + TempNumber][Y].Fish + 1]++;
        TempNumber++;
    }
    TempNumber = 1;
    while (TempGame->Map[X - TempNumber][Y].Fish != 0 && TempGame->Map[X - TempNumber][Y].Player == -1)
    {
        Potential[TempGame->Map[X - TempNumber][Y].Fish + 1]++;
        TempNumber++;
    }
    TempNumber = 1;
    while (TempGame->Map[X][Y + TempNumber].Fish != 0 && TempGame->Map[X][Y + TempNumber].Player == -1)
    {
        Potential[TempGame->Map[X][Y + TempNumber].Fish + 1]++;
        TempNumber++;
    }
    TempNumber = 1;
    while (TempGame->Map[X][Y - TempNumber].Fish != 0 && TempGame->Map[X][Y - TempNumber].Player == -1)
    {
        Potential[TempGame->Map[X][Y - TempNumber].Fish + 1]++;
        TempNumber++;
    }
}
int compair_potential(int *Potential1, int *Potential2)
{
    int Result = 0;
    for (int i = 4; i > 1; i--)
    {
        if (Potential1[i] > Potential2[i])
        {
            Result = -1;
        }
        if (Potential1[i] < Potential2[i])
        {
            Result = 1;
        }
        if (Result != 0)
        {
            break;
        }
    }
    return Result;
}
void find_all_cells_with_1(struct Game *TempGame, int (*TempCellWith1)[4], int *CountCell)
{
    CountCell[0] = 0;
    CountCell[1] = 0;
    for (int x = 0; x < TempGame->SizeMapX + 2; x++)
    {
        for (int y = 0; y < TempGame->SizeMapY + 2; y++)
        {
            if (TempGame->Map[x][y].Fish == 1 && TempGame->Map[x][y].Player == -1)
            {
                if (x == 1 || y == 1 || x == TempGame->SizeMapX || y == TempGame->SizeMapY)
                {
                    TempCellWith1[CountCell[1]][2] = x;
                    TempCellWith1[CountCell[1]][3] = y;
                    CountCell[1]++;
                }
                else
                {
                    TempCellWith1[CountCell[0]][0] = x;
                    TempCellWith1[CountCell[0]][1] = y;
                    CountCell[0]++;
                }
            }
        }
    }
}
int bot_put_penguin(struct Game *TempGame)
{
    int CellWith1[10000][4], Set[100][6], CounterSet = 0, NumberCellWith1[2], x, y, RandomNumber;
    Set[0][2] = 0;
    Set[0][3] = 0;
    Set[0][4] = 0;
    find_all_cells_with_1(TempGame, CellWith1, NumberCellWith1);
    if (NumberCellWith1[0] == 0 && NumberCellWith1[1] == 0)
    {
        return 1;
    }
    if (NumberCellWith1[0] > 0)
    {
        for (int i = 0; i < NumberCellWith1[0]; i++)
        {
            count_potential(Set[CounterSet], CellWith1[i][0], CellWith1[i][1], TempGame);
            if (CounterSet == 0)
            {
                Set[CounterSet][0] = CellWith1[i][0];
                Set[CounterSet][1] = CellWith1[i][1];
                CounterSet++;
            }
            else
            {
                if (compair_potential(Set[CounterSet - 1], Set[CounterSet]) > 0)
                {
                    Set[0][0] = CellWith1[i][0];
                    Set[0][1] = CellWith1[i][1];
                    Set[0][2] = Set[CounterSet][2];
                    Set[0][3] = Set[CounterSet][3];
                    Set[0][4] = Set[CounterSet][4];
                    CounterSet = 1;
                }
                else
                {
                    if (compair_potential(Set[CounterSet - 1], Set[CounterSet]) == 0)
                    {
                        Set[CounterSet][0] = CellWith1[i][0];
                        Set[CounterSet][1] = CellWith1[i][1];
                        CounterSet++;
                    }
                }
            }
        }
    }
    else
    {
        for (int i = 0; i < NumberCellWith1[1]; i++)
        {
            count_potential(Set[CounterSet], CellWith1[i][2], CellWith1[i][3], TempGame);
            if (CounterSet == 0)
            {
                Set[CounterSet][0] = CellWith1[i][2];
                Set[CounterSet][1] = CellWith1[i][3];
                CounterSet++;
            }
            else
            {
                if (compair_potential(Set[CounterSet - 1], Set[CounterSet]) > 0)
                {
                    Set[0][0] = CellWith1[i][2];
                    Set[0][1] = CellWith1[i][3];
                    Set[0][2] = Set[CounterSet][2];
                    Set[0][3] = Set[CounterSet][3];
                    Set[0][4] = Set[CounterSet][4];
                    CounterSet = 1;
                }
                else
                {
                    if (compair_potential(Set[CounterSet - 1], Set[CounterSet]) == 0)
                    {
                        Set[CounterSet][0] = CellWith1[i][2];
                        Set[CounterSet][1] = CellWith1[i][3];
                        CounterSet++;
                    }
                }
            }
        }
    }
    RandomNumber = rand() % (CounterSet);
    x = Set[RandomNumber][0];
    y = Set[RandomNumber][1];
    TempGame->Map[x][y].Player = TempGame->MyNumber;
    TempGame->Player[TempGame->MyNumber].Score += TempGame->Map[x][y].Fish;
    TempGame->Player[TempGame->MyNumber].NumberOfPenguins++;
    return 0;
}
void bot_make_turn(struct Game *TempGame)
{
    int ChoosePenguin, Set[100][6], CounterSet = 0, TempNumber, x, y, Prop, MinFish, *ListOfPenguins, CounterOfPenguins;
    ListOfPenguins = (int *)calloc(TempGame->NumPenguins, sizeof(int));
    CounterOfPenguins = choose_penguins(ListOfPenguins, TempGame);
    ChoosePenguin = ListOfPenguins[rand() % CounterOfPenguins];
    CounterSet = 0;
    Set[0][2] = 0;
    Set[0][3] = 0;
    Set[0][4] = 0;
    Set[0][5] = 999999;
    Prop = 2;
    MinFish = 3;
    do
    {
        TempNumber = 1;
        while (TempGame->Map[TempGame->Player[TempGame->MyNumber].Penguin[ChoosePenguin].PositionX + TempNumber][TempGame->Player[TempGame->MyNumber].Penguin[ChoosePenguin].PositionY].Fish != 0 || TempGame->Map[TempGame->Player[TempGame->MyNumber].Penguin[ChoosePenguin].PositionX + TempNumber][TempGame->Player[TempGame->MyNumber].Penguin[ChoosePenguin].PositionY].Player != -1)
        {
            if (count_direction(TempGame->Player[TempGame->MyNumber].Penguin[ChoosePenguin].PositionX + TempNumber, TempGame->Player[TempGame->MyNumber].Penguin[ChoosePenguin].PositionY, TempGame) >= Prop && TempGame->Map[TempGame->Player[TempGame->MyNumber].Penguin[ChoosePenguin].PositionX + TempNumber][TempGame->Player[TempGame->MyNumber].Penguin[ChoosePenguin].PositionY].Fish >= MinFish)
            {
                count_potential(Set[CounterSet], TempGame->Player[TempGame->MyNumber].Penguin[ChoosePenguin].PositionX + TempNumber, TempGame->Player[TempGame->MyNumber].Penguin[ChoosePenguin].PositionY, TempGame);
                if (CounterSet == 0)
                {
                    Set[CounterSet][0] = TempGame->Player[TempGame->MyNumber].Penguin[ChoosePenguin].PositionX + TempNumber;
                    Set[CounterSet][1] = TempGame->Player[TempGame->MyNumber].Penguin[ChoosePenguin].PositionY;
                    Set[CounterSet][5] = TempNumber;
                    CounterSet++;
                }
                else
                {
                    if (compair_potential(Set[CounterSet - 1], Set[CounterSet]) > 0)
                    {
                        Set[0][0] = TempGame->Player[TempGame->MyNumber].Penguin[ChoosePenguin].PositionX + TempNumber;
                        Set[0][1] = TempGame->Player[TempGame->MyNumber].Penguin[ChoosePenguin].PositionY;
                        Set[0][2] = Set[CounterSet][2];
                        Set[0][3] = Set[CounterSet][3];
                        Set[0][4] = Set[CounterSet][4];
                        Set[0][5] = TempNumber;
                        CounterSet = 1;
                    }
                    else
                    {
                        if (compair_potential(Set[CounterSet - 1], Set[CounterSet]) == 0 && Set[CounterSet - 1][5] > TempNumber)
                        {
                            Set[0][0] = TempGame->Player[TempGame->MyNumber].Penguin[ChoosePenguin].PositionX + TempNumber;
                            Set[0][1] = TempGame->Player[TempGame->MyNumber].Penguin[ChoosePenguin].PositionY;
                            Set[0][2] = Set[CounterSet][2];
                            Set[0][3] = Set[CounterSet][3];
                            Set[0][4] = Set[CounterSet][4];
                            Set[0][5] = TempNumber;
                            CounterSet = 1;
                        }
                    }
                }
            }
            TempNumber++;
        }
        TempNumber = 1;
        while (TempGame->Map[TempGame->Player[TempGame->MyNumber].Penguin[ChoosePenguin].PositionX - TempNumber][TempGame->Player[TempGame->MyNumber].Penguin[ChoosePenguin].PositionY].Fish != 0 || TempGame->Map[TempGame->Player[TempGame->MyNumber].Penguin[ChoosePenguin].PositionX - TempNumber][TempGame->Player[TempGame->MyNumber].Penguin[ChoosePenguin].PositionY].Player != -1)
        {
            if (count_direction(TempGame->Player[TempGame->MyNumber].Penguin[ChoosePenguin].PositionX - TempNumber, TempGame->Player[TempGame->MyNumber].Penguin[ChoosePenguin].PositionY, TempGame) >= Prop && TempGame->Map[TempGame->Player[TempGame->MyNumber].Penguin[ChoosePenguin].PositionX - TempNumber][TempGame->Player[TempGame->MyNumber].Penguin[ChoosePenguin].PositionY].Fish >= MinFish)
            {
                count_potential(Set[CounterSet], TempGame->Player[TempGame->MyNumber].Penguin[ChoosePenguin].PositionX - TempNumber, TempGame->Player[TempGame->MyNumber].Penguin[ChoosePenguin].PositionY, TempGame);
                if (CounterSet == 0)
                {
                    Set[CounterSet][0] = TempGame->Player[TempGame->MyNumber].Penguin[ChoosePenguin].PositionX - TempNumber;
                    Set[CounterSet][1] = TempGame->Player[TempGame->MyNumber].Penguin[ChoosePenguin].PositionY;
                    CounterSet++;
                }
                else
                {
                    if (compair_potential(Set[CounterSet - 1], Set[CounterSet]) > 0)
                    {
                        Set[0][0] = TempGame->Player[TempGame->MyNumber].Penguin[ChoosePenguin].PositionX - TempNumber;
                        Set[0][1] = TempGame->Player[TempGame->MyNumber].Penguin[ChoosePenguin].PositionY;
                        Set[0][2] = Set[CounterSet][2];
                        Set[0][3] = Set[CounterSet][3];
                        Set[0][4] = Set[CounterSet][4];
                        CounterSet = 1;
                    }
                    else
                    {
                        if (compair_potential(Set[CounterSet - 1], Set[CounterSet]) == 0 && Set[CounterSet - 1][5] > TempNumber)
                        {
                            Set[0][0] = TempGame->Player[TempGame->MyNumber].Penguin[ChoosePenguin].PositionX - TempNumber;
                            Set[0][1] = TempGame->Player[TempGame->MyNumber].Penguin[ChoosePenguin].PositionY;
                            Set[0][2] = Set[CounterSet][2];
                            Set[0][3] = Set[CounterSet][3];
                            Set[0][4] = Set[CounterSet][4];
                            Set[0][5] = TempNumber;
                            CounterSet = 1;
                        }
                    }
                }
            }
            TempNumber++;
        }
        TempNumber = 1;
        while (TempGame->Map[TempGame->Player[TempGame->MyNumber].Penguin[ChoosePenguin].PositionX][TempGame->Player[TempGame->MyNumber].Penguin[ChoosePenguin].PositionY + TempNumber].Fish != 0 || TempGame->Map[TempGame->Player[TempGame->MyNumber].Penguin[ChoosePenguin].PositionX][TempGame->Player[TempGame->MyNumber].Penguin[ChoosePenguin].PositionY + TempNumber].Player != -1)
        {
            if (count_direction(TempGame->Player[TempGame->MyNumber].Penguin[ChoosePenguin].PositionX, TempGame->Player[TempGame->MyNumber].Penguin[ChoosePenguin].PositionY + TempNumber, TempGame) >= Prop && TempGame->Map[TempGame->Player[TempGame->MyNumber].Penguin[ChoosePenguin].PositionX][TempGame->Player[TempGame->MyNumber].Penguin[ChoosePenguin].PositionY + TempNumber].Fish >= MinFish)
            {
                count_potential(Set[CounterSet], TempGame->Player[TempGame->MyNumber].Penguin[ChoosePenguin].PositionX, TempGame->Player[TempGame->MyNumber].Penguin[ChoosePenguin].PositionY + TempNumber, TempGame);
                if (CounterSet == 0)
                {
                    Set[CounterSet][0] = TempGame->Player[TempGame->MyNumber].Penguin[ChoosePenguin].PositionX;
                    Set[CounterSet][1] = TempGame->Player[TempGame->MyNumber].Penguin[ChoosePenguin].PositionY + TempNumber;
                    CounterSet++;
                }
                else
                {
                    if (compair_potential(Set[CounterSet - 1], Set[CounterSet]) > 0)
                    {
                        Set[0][0] = TempGame->Player[TempGame->MyNumber].Penguin[ChoosePenguin].PositionX;
                        Set[0][1] = TempGame->Player[TempGame->MyNumber].Penguin[ChoosePenguin].PositionY + TempNumber;
                        Set[0][2] = Set[CounterSet][2];
                        Set[0][3] = Set[CounterSet][3];
                        Set[0][4] = Set[CounterSet][4];
                        CounterSet = 1;
                    }
                    else
                    {
                        if (compair_potential(Set[CounterSet - 1], Set[CounterSet]) == 0 && Set[CounterSet - 1][5] > TempNumber)
                        {
                            Set[0][0] = TempGame->Player[TempGame->MyNumber].Penguin[ChoosePenguin].PositionX;
                            Set[0][1] = TempGame->Player[TempGame->MyNumber].Penguin[ChoosePenguin].PositionY + TempNumber;
                            Set[0][2] = Set[CounterSet][2];
                            Set[0][3] = Set[CounterSet][3];
                            Set[0][4] = Set[CounterSet][4];
                            Set[0][5] = TempNumber;
                            CounterSet = 1;
                        }
                    }
                }
            }
            TempNumber++;
        }
        TempNumber = 1;
        while (TempGame->Map[TempGame->Player[TempGame->MyNumber].Penguin[ChoosePenguin].PositionX][TempGame->Player[TempGame->MyNumber].Penguin[ChoosePenguin].PositionY - TempNumber].Fish != 0 || TempGame->Map[TempGame->Player[TempGame->MyNumber].Penguin[ChoosePenguin].PositionX][TempGame->Player[TempGame->MyNumber].Penguin[ChoosePenguin].PositionY - TempNumber].Player != -1)
        {
            if (count_direction(TempGame->Player[TempGame->MyNumber].Penguin[ChoosePenguin].PositionX, TempGame->Player[TempGame->MyNumber].Penguin[ChoosePenguin].PositionY - TempNumber, TempGame) >= Prop && TempGame->Map[TempGame->Player[TempGame->MyNumber].Penguin[ChoosePenguin].PositionX][TempGame->Player[TempGame->MyNumber].Penguin[ChoosePenguin].PositionY - TempNumber].Fish >= MinFish)
            {
                count_potential(Set[CounterSet], TempGame->Player[TempGame->MyNumber].Penguin[ChoosePenguin].PositionX, TempGame->Player[TempGame->MyNumber].Penguin[ChoosePenguin].PositionY - TempNumber, TempGame);
                if (CounterSet == 0)
                {
                    Set[CounterSet][0] = TempGame->Player[TempGame->MyNumber].Penguin[ChoosePenguin].PositionX;
                    Set[CounterSet][1] = TempGame->Player[TempGame->MyNumber].Penguin[ChoosePenguin].PositionY - TempNumber;
                    CounterSet++;
                }
                else
                {
                    if (compair_potential(Set[CounterSet - 1], Set[CounterSet]) > 0)
                    {
                        Set[0][0] = TempGame->Player[TempGame->MyNumber].Penguin[ChoosePenguin].PositionX;
                        Set[0][1] = TempGame->Player[TempGame->MyNumber].Penguin[ChoosePenguin].PositionY - TempNumber;
                        Set[0][2] = Set[CounterSet][2];
                        Set[0][3] = Set[CounterSet][3];
                        Set[0][4] = Set[CounterSet][4];
                        CounterSet = 1;
                    }
                    else
                    {
                        if (compair_potential(Set[CounterSet - 1], Set[CounterSet]) == 0 && Set[CounterSet - 1][5] > TempNumber)
                        {
                            Set[0][0] = TempGame->Player[TempGame->MyNumber].Penguin[ChoosePenguin].PositionX;
                            Set[0][1] = TempGame->Player[TempGame->MyNumber].Penguin[ChoosePenguin].PositionY - TempNumber;
                            Set[0][2] = Set[CounterSet][2];
                            Set[0][3] = Set[CounterSet][3];
                            Set[0][4] = Set[CounterSet][4];
                            Set[0][5] = TempNumber;
                            CounterSet = 1;
                        }
                    }
                }
            }
            TempNumber++;
        }
        Prop--;
        if (Prop == 0 && MinFish > 1)
        {
            MinFish--;
            Prop = 2;
        }
    } while (CounterSet == 0);
    x = Set[0][0];
    y = Set[0][1];
    TempGame->Player[TempGame->MyNumber].Score = TempGame->Player[TempGame->MyNumber].Score + TempGame->Map[x][y].Fish;
    TempGame->Map[x][y].Player = TempGame->MyNumber;
    TempGame->Map[TempGame->Player[TempGame->MyNumber].Penguin[ChoosePenguin].PositionX][TempGame->Player[TempGame->MyNumber].Penguin[ChoosePenguin].PositionY].Player = -1;
    TempGame->Map[TempGame->Player[TempGame->MyNumber].Penguin[ChoosePenguin].PositionX][TempGame->Player[TempGame->MyNumber].Penguin[ChoosePenguin].PositionY].Fish = 0;
    free(ListOfPenguins);
}