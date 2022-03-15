int choose_penguins(int IDPlayer, int *ListOfPenguins, struct Game *TempGame)
{
    int NumberOfSide, CounterOfPenguins = 0;
    for (int i = 0; i < TempGame->NumPenguins; i++)
    {
        NumberOfSide = 4;
        if (TempGame->Map[TempGame->Player[IDPlayer].Penguin[i].PositionX + 1][TempGame->Player[IDPlayer].Penguin[i].PositionY].Fish == 0)
        {
            NumberOfSide--;
        }
        if (TempGame->Map[TempGame->Player[IDPlayer].Penguin[i].PositionX - 1][TempGame->Player[IDPlayer].Penguin[i].PositionY].Fish == 0)
        {
            NumberOfSide--;
        }
        if (TempGame->Map[TempGame->Player[IDPlayer].Penguin[i].PositionX][TempGame->Player[IDPlayer].Penguin[i].PositionY + 1].Fish == 0)
        {
            NumberOfSide--;
        }
        if (TempGame->Map[TempGame->Player[IDPlayer].Penguin[i].PositionX][TempGame->Player[IDPlayer].Penguin[i].PositionY - 1].Fish == 0)
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
        for (int i = 0; i < TempGame->NumPenguins; i++)
        {
            if (TempGame->Player[IDPlayer].Penguin[i].Movable == 0)
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
    if (TempGame->Map[x][y - 1].Fish != 0)
    {
        Counter++;
    }
    if (TempGame->Map[x][y + 1].Fish != 0)
    {
        Counter++;
    }
    if (TempGame->Map[x + 1][y].Fish != 0)
    {
        Counter++;
    }
    if (TempGame->Map[x - 1][y].Fish != 0)
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
    while (TempGame->Map[X + TempNumber][Y].Fish != 0)
    {
        Potential[TempGame->Map[X + TempNumber][Y].Fish + 1]++;
        TempNumber++;
    }
    TempNumber = 1;
    while (TempGame->Map[X - TempNumber][Y].Fish != 0)
    {
        Potential[TempGame->Map[X - TempNumber][Y].Fish + 1]++;
        TempNumber++;
    }
    TempNumber = 1;
    while (TempGame->Map[X][Y + TempNumber].Fish != 0)
    {
        Potential[TempGame->Map[X][Y + TempNumber].Fish + 1]++;
        TempNumber++;
    }
    TempNumber = 1;
    while (TempGame->Map[X][Y - TempNumber].Fish != 0)
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
int compair_potential_Vers_II(int *Potential1, int *Potential2)
{
    // int Result = 0;
    // if (Potential1[4] * 3 + Potential1[3] * 2 + Potential1[2] > Potential2[4] * 3 + Potential2[3] * 2 + Potential2[2])
    // {
    //     Result = -1;
    // }
    // if (Potential1[4] * 3 + Potential1[3] * 2 + Potential1[2] < Potential2[4] * 3 + Potential2[3] * 2 + Potential2[2])
    // {
    //     Result = 1;
    // }
    // return Result;
    int Result = 0;
    if (pow(Potential1[4], 4) + pow(Potential1[3], 2) + Potential1[2] > pow(Potential2[4], 4) + pow(Potential2[3], 2) + Potential2[2])
    {
        Result = -1;
    }
    if (pow(Potential1[4], 4) + pow(Potential1[3], 2) + Potential1[2] < pow(Potential2[4], 4) + pow(Potential2[3], 2) + Potential2[2])
    {
        Result = 1;
    }
    return Result;
}
void find_all_cells_with_1(struct Game *TempGame, int **TempCellWith1, int *CountCell)
{
    CountCell[0] = 0;
    CountCell[1] = 0;
    for (int x = 0; x < TempGame->SizeMapX + 2; x++)
    {
        for (int y = 0; y < TempGame->SizeMapY + 2; y++)
        {
            if (TempGame->Map[x][y].Fish == 1)
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
void random_put_penguin(int IDPlayer, int IDPenguin, struct Game *TempGame)
{
    int **CellWith1, NumberCellWith1[2], x, y, RandomNumber;
    CellWith1 = (int **)calloc(TempGame->SizeMapX * TempGame->SizeMapY, sizeof(int *));
    for (int i = 0; i < TempGame->SizeMapX * TempGame->SizeMapY; i++)
    {
        CellWith1[i] = (int *)calloc(4, sizeof(int));
    }
    find_all_cells_with_1(TempGame, CellWith1, NumberCellWith1);
    if (NumberCellWith1[0] > 0)
    {
        RandomNumber = rand() % (NumberCellWith1[0]);
        x = CellWith1[RandomNumber][0];
        y = CellWith1[RandomNumber][1];
    }
    else
    {
        RandomNumber = rand() % (NumberCellWith1[1]);
        x = CellWith1[RandomNumber][2];
        y = CellWith1[RandomNumber][3];
    }
    TempGame->Player[IDPlayer].Penguin[IDPenguin].PositionX = x;
    TempGame->Player[IDPlayer].Penguin[IDPenguin].PositionY = y;
    TempGame->Player[IDPlayer].Penguin[IDPenguin].Movable = 0;
    TempGame->Map[x][y].Player = IDPlayer;
    TempGame->Map[x][y].Penguin = IDPenguin;
    TempGame->Player[IDPlayer].Score = TempGame->Map[x][y].Fish;
    TempGame->Map[x][y].Fish = 0;
    for (int i = 0; i < TempGame->SizeMapX * TempGame->SizeMapY; i++)
    {
        free(CellWith1[i]);
    }
    free(CellWith1);
}
void put_penguin_with_potential(int IDPlayer, int IDPenguin, struct Game *TempGame)
{
    int **CellWith1, Set[100][6], CounterSet = 0, NumberCellWith1[2], x, y, RandomNumber;
    Set[0][2] = 0;
    Set[0][3] = 0;
    Set[0][4] = 0;
    CellWith1 = (int **)calloc(TempGame->SizeMapX * TempGame->SizeMapY, sizeof(int *));
    for (int i = 0; i < TempGame->SizeMapX * TempGame->SizeMapY; i++)
    {
        CellWith1[i] = (int *)calloc(4, sizeof(int));
    }
    find_all_cells_with_1(TempGame, CellWith1, NumberCellWith1);
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
    TempGame->Player[IDPlayer].Penguin[IDPenguin].PositionX = x;
    TempGame->Player[IDPlayer].Penguin[IDPenguin].PositionY = y;
    TempGame->Player[IDPlayer].Penguin[IDPenguin].Movable = 0;
    TempGame->Map[x][y].Player = IDPlayer;
    TempGame->Map[x][y].Penguin = IDPenguin;
    TempGame->Player[IDPlayer].Score += TempGame->Map[x][y].Fish;
    TempGame->Map[x][y].Fish = 0;
    for (int i = 0; i < TempGame->SizeMapX * TempGame->SizeMapY; i++)
    {
        free(CellWith1[i]);
    }
    free(CellWith1);
}
void put_penguin_with_potential_Vers_II(int IDPlayer, int IDPenguin, struct Game *TempGame)
{
    int **CellWith1, Set[100][6], CounterSet = 0, NumberCellWith1[2], x, y, RandomNumber;
    Set[0][2] = 0;
    Set[0][3] = 0;
    Set[0][4] = 0;
    CellWith1 = (int **)calloc(TempGame->SizeMapX * TempGame->SizeMapY, sizeof(int *));
    for (int i = 0; i < TempGame->SizeMapX * TempGame->SizeMapY; i++)
    {
        CellWith1[i] = (int *)calloc(4, sizeof(int));
    }
    find_all_cells_with_1(TempGame, CellWith1, NumberCellWith1);
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
                if (compair_potential_Vers_II(Set[CounterSet - 1], Set[CounterSet]) > 0)
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
                    if (compair_potential_Vers_II(Set[CounterSet - 1], Set[CounterSet]) == 0)
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
                if (compair_potential_Vers_II(Set[CounterSet - 1], Set[CounterSet]) > 0)
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
                    if (compair_potential_Vers_II(Set[CounterSet - 1], Set[CounterSet]) == 0)
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
    TempGame->Player[IDPlayer].Penguin[IDPenguin].PositionX = x;
    TempGame->Player[IDPlayer].Penguin[IDPenguin].PositionY = y;
    TempGame->Player[IDPlayer].Penguin[IDPenguin].Movable = 0;
    TempGame->Map[x][y].Player = IDPlayer;
    TempGame->Map[x][y].Penguin = IDPenguin;
    TempGame->Player[IDPlayer].Score += TempGame->Map[x][y].Fish;
    TempGame->Map[x][y].Fish = 0;
    for (int i = 0; i < TempGame->SizeMapX * TempGame->SizeMapY; i++)
    {
        free(CellWith1[i]);
    }
    free(CellWith1);
}
void bot_level_1(int IDPlayer, struct Game *TempGame)
{
    int ChoosePenguin, Set[100][2], CounterSet = 0, TempNumber, x, y;
    for (int i = 0; i < TempGame->NumPenguins; i++)
    {
        if (TempGame->Player[IDPlayer].Penguin[i].Movable == 0)
        {
            Set[CounterSet][0] = i;
            CounterSet++;
        }
    }
    ChoosePenguin = Set[rand() % CounterSet][0];
    CounterSet = 0;
    TempNumber = 1;
    while (TempGame->Map[TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionX + TempNumber][TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionY].Fish != 0)
    {
        Set[CounterSet][0] = TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionX + TempNumber;
        Set[CounterSet][1] = TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionY;
        TempNumber++;
        CounterSet++;
    }
    TempNumber = 1;
    while (TempGame->Map[TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionX - TempNumber][TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionY].Fish != 0)
    {
        Set[CounterSet][0] = TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionX - TempNumber;
        Set[CounterSet][1] = TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionY;
        TempNumber++;
        CounterSet++;
    }
    TempNumber = 1;
    while (TempGame->Map[TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionX][TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionY + TempNumber].Fish != 0)
    {
        Set[CounterSet][0] = TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionX;
        Set[CounterSet][1] = TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionY + TempNumber;
        TempNumber++;
        CounterSet++;
    }
    TempNumber = 1;
    while (TempGame->Map[TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionX][TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionY - TempNumber].Fish != 0)
    {
        Set[CounterSet][0] = TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionX;
        Set[CounterSet][1] = TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionY - TempNumber;
        TempNumber++;
        CounterSet++;
    }
    TempNumber = rand() % CounterSet;
    x = Set[TempNumber][0];
    y = Set[TempNumber][1];
    TempGame->Player[IDPlayer].Score = TempGame->Player[IDPlayer].Score + TempGame->Map[x][y].Fish;
    TempGame->Map[x][y].Fish = 0;
    TempGame->Map[x][y].Player = IDPlayer;
    TempGame->Map[x][y].Penguin = ChoosePenguin;
    TempGame->Map[TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionX][TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionY].Player = -1;
    TempGame->Map[TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionX][TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionY].Penguin = -1;
    TempGame->Player[IDPlayer].Penguin[TempGame->Map[x][y].Penguin].PositionX = x;
    TempGame->Player[IDPlayer].Penguin[TempGame->Map[x][y].Penguin].PositionY = y;
    TempGame->Player[IDPlayer].Penguin[TempGame->Map[x][y].Penguin].Movable = check_penguin(x, y, TempGame);
    if (TempGame->Map[x + 1][y].Player != -1)
    {
        TempGame->Player[TempGame->Map[x + 1][y].Player].Penguin[TempGame->Map[x + 1][y].Penguin].Movable = check_penguin(x + 1, y, TempGame);
    }
    if (TempGame->Map[x - 1][y].Player != -1)
    {
        TempGame->Player[TempGame->Map[x - 1][y].Player].Penguin[TempGame->Map[x - 1][y].Penguin].Movable = check_penguin(x - 1, y, TempGame);
    }
    if (TempGame->Map[x][y + 1].Player != -1)
    {
        TempGame->Player[TempGame->Map[x][y + 1].Player].Penguin[TempGame->Map[x][y + 1].Penguin].Movable = check_penguin(x, y + 1, TempGame);
    }
    if (TempGame->Map[x][y - 1].Player != -1)
    {
        TempGame->Player[TempGame->Map[x][y - 1].Player].Penguin[TempGame->Map[x][y - 1].Penguin].Movable = check_penguin(x, y - 1, TempGame);
    }
    if (TempGame->Player[TempGame->NumPlayers - 1].BotNumber != TempGame->NumPlayers)
    {
        print_map(TempGame);
    }
}
void bot_level_2(int IDPlayer, struct Game *TempGame)
{
    int ChoosePenguin, Set[100][2], CounterSet = 0, TempNumber, x, y, Prop = 3, *ListOfPenguins, CounterOfPenguins;
    ListOfPenguins = (int *)calloc(TempGame->NumPenguins, sizeof(int));
    CounterOfPenguins = choose_penguins(IDPlayer, ListOfPenguins, TempGame);
    ChoosePenguin = ListOfPenguins[rand() % CounterOfPenguins];
    CounterSet = 0;
    Prop = 2;
    do
    {
        TempNumber = 1;
        while (TempGame->Map[TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionX + TempNumber][TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionY].Fish != 0)
        {
            if (count_direction(TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionX + TempNumber, TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionY, TempGame) >= Prop)
            {
                Set[CounterSet][0] = TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionX + TempNumber;
                Set[CounterSet][1] = TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionY;
                CounterSet++;
            }
            TempNumber++;
        }
        TempNumber = 1;
        while (TempGame->Map[TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionX - TempNumber][TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionY].Fish != 0)
        {
            if (count_direction(TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionX - TempNumber, TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionY, TempGame) >= Prop)
            {
                Set[CounterSet][0] = TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionX - TempNumber;
                Set[CounterSet][1] = TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionY;
                CounterSet++;
            }
            TempNumber++;
        }
        TempNumber = 1;
        while (TempGame->Map[TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionX][TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionY + TempNumber].Fish != 0)
        {
            if (count_direction(TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionX, TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionY + TempNumber, TempGame) >= Prop)
            {
                Set[CounterSet][0] = TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionX;
                Set[CounterSet][1] = TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionY + TempNumber;
                CounterSet++;
            }
            TempNumber++;
        }
        TempNumber = 1;
        while (TempGame->Map[TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionX][TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionY - TempNumber].Fish != 0)
        {
            if (count_direction(TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionX, TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionY - TempNumber, TempGame) >= Prop)
            {
                Set[CounterSet][0] = TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionX;
                Set[CounterSet][1] = TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionY - TempNumber;
                CounterSet++;
            }
            TempNumber++;
        }
        Prop--;
    } while (CounterSet == 0);
    TempNumber = rand() % CounterSet;
    x = Set[TempNumber][0];
    y = Set[TempNumber][1];
    TempGame->Player[IDPlayer].Score = TempGame->Player[IDPlayer].Score + TempGame->Map[x][y].Fish;
    TempGame->Map[x][y].Fish = 0;
    TempGame->Map[x][y].Player = IDPlayer;
    TempGame->Map[x][y].Penguin = ChoosePenguin;
    TempGame->Map[TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionX][TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionY].Player = -1;
    TempGame->Map[TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionX][TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionY].Penguin = -1;
    TempGame->Player[IDPlayer].Penguin[TempGame->Map[x][y].Penguin].PositionX = x;
    TempGame->Player[IDPlayer].Penguin[TempGame->Map[x][y].Penguin].PositionY = y;
    TempGame->Player[IDPlayer].Penguin[TempGame->Map[x][y].Penguin].Movable = check_penguin(x, y, TempGame);
    if (TempGame->Map[x + 1][y].Player != -1)
    {
        TempGame->Player[TempGame->Map[x + 1][y].Player].Penguin[TempGame->Map[x + 1][y].Penguin].Movable = check_penguin(x + 1, y, TempGame);
    }
    if (TempGame->Map[x - 1][y].Player != -1)
    {
        TempGame->Player[TempGame->Map[x - 1][y].Player].Penguin[TempGame->Map[x - 1][y].Penguin].Movable = check_penguin(x - 1, y, TempGame);
    }
    if (TempGame->Map[x][y + 1].Player != -1)
    {
        TempGame->Player[TempGame->Map[x][y + 1].Player].Penguin[TempGame->Map[x][y + 1].Penguin].Movable = check_penguin(x, y + 1, TempGame);
    }
    if (TempGame->Map[x][y - 1].Player != -1)
    {
        TempGame->Player[TempGame->Map[x][y - 1].Player].Penguin[TempGame->Map[x][y - 1].Penguin].Movable = check_penguin(x, y - 1, TempGame);
    }
    if (TempGame->Player[TempGame->NumPlayers - 1].BotNumber != TempGame->NumPlayers)
    {
        print_map(TempGame);
    }
    free(ListOfPenguins);
}
void bot_level_3(int IDPlayer, struct Game *TempGame)
{
    int ChoosePenguin, Set[100][2], CounterSet = 0, TempNumber, x, y, Prop, MinFish, *ListOfPenguins, CounterOfPenguins;
    ListOfPenguins = (int *)calloc(TempGame->NumPenguins, sizeof(int));
    CounterOfPenguins = choose_penguins(IDPlayer, ListOfPenguins, TempGame);
    ChoosePenguin = ListOfPenguins[rand() % CounterOfPenguins];
    CounterSet = 0;
    Prop = 2;
    MinFish = 3;
    do
    {
        TempNumber = 1;
        while (TempGame->Map[TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionX + TempNumber][TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionY].Fish != 0)
        {
            if (count_direction(TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionX + TempNumber, TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionY, TempGame) >= Prop && TempGame->Map[TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionX + TempNumber][TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionY].Fish >= MinFish)
            {
                Set[CounterSet][0] = TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionX + TempNumber;
                Set[CounterSet][1] = TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionY;
                CounterSet++;
            }
            TempNumber++;
        }
        TempNumber = 1;
        while (TempGame->Map[TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionX - TempNumber][TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionY].Fish != 0)
        {
            if (count_direction(TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionX - TempNumber, TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionY, TempGame) >= Prop && TempGame->Map[TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionX - TempNumber][TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionY].Fish >= MinFish)
            {
                Set[CounterSet][0] = TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionX - TempNumber;
                Set[CounterSet][1] = TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionY;
                CounterSet++;
            }
            TempNumber++;
        }
        TempNumber = 1;
        while (TempGame->Map[TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionX][TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionY + TempNumber].Fish != 0)
        {
            if (count_direction(TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionX, TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionY + TempNumber, TempGame) >= Prop && TempGame->Map[TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionX][TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionY + TempNumber].Fish >= MinFish)
            {
                Set[CounterSet][0] = TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionX;
                Set[CounterSet][1] = TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionY + TempNumber;
                CounterSet++;
            }
            TempNumber++;
        }
        TempNumber = 1;
        while (TempGame->Map[TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionX][TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionY - TempNumber].Fish != 0)
        {
            if (count_direction(TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionX, TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionY - TempNumber, TempGame) >= Prop && TempGame->Map[TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionX][TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionY - TempNumber].Fish >= MinFish)
            {
                Set[CounterSet][0] = TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionX;
                Set[CounterSet][1] = TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionY - TempNumber;
                CounterSet++;
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
    TempNumber = rand() % CounterSet;
    x = Set[TempNumber][0];
    y = Set[TempNumber][1];
    TempGame->Player[IDPlayer].Score = TempGame->Player[IDPlayer].Score + TempGame->Map[x][y].Fish;
    TempGame->Map[x][y].Fish = 0;
    TempGame->Map[x][y].Player = IDPlayer;
    TempGame->Map[x][y].Penguin = ChoosePenguin;
    TempGame->Map[TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionX][TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionY].Player = -1;
    TempGame->Map[TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionX][TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionY].Penguin = -1;
    TempGame->Player[IDPlayer].Penguin[TempGame->Map[x][y].Penguin].PositionX = x;
    TempGame->Player[IDPlayer].Penguin[TempGame->Map[x][y].Penguin].PositionY = y;
    TempGame->Player[IDPlayer].Penguin[TempGame->Map[x][y].Penguin].Movable = check_penguin(x, y, TempGame);
    if (TempGame->Map[x + 1][y].Player != -1)
    {
        TempGame->Player[TempGame->Map[x + 1][y].Player].Penguin[TempGame->Map[x + 1][y].Penguin].Movable = check_penguin(x + 1, y, TempGame);
    }
    if (TempGame->Map[x - 1][y].Player != -1)
    {
        TempGame->Player[TempGame->Map[x - 1][y].Player].Penguin[TempGame->Map[x - 1][y].Penguin].Movable = check_penguin(x - 1, y, TempGame);
    }
    if (TempGame->Map[x][y + 1].Player != -1)
    {
        TempGame->Player[TempGame->Map[x][y + 1].Player].Penguin[TempGame->Map[x][y + 1].Penguin].Movable = check_penguin(x, y + 1, TempGame);
    }
    if (TempGame->Map[x][y - 1].Player != -1)
    {
        TempGame->Player[TempGame->Map[x][y - 1].Player].Penguin[TempGame->Map[x][y - 1].Penguin].Movable = check_penguin(x, y - 1, TempGame);
    }
    if (TempGame->Player[TempGame->NumPlayers - 1].BotNumber != TempGame->NumPlayers)
    {
        print_map(TempGame);
    }
    free(ListOfPenguins);
}
void bot_level_4(int IDPlayer, struct Game *TempGame)
{
    int ChoosePenguin, Set[100][2], CounterSet = 0, TempNumber, x, y, Prop, MinFish, *ListOfPenguins, CounterOfPenguins;
    ListOfPenguins = (int *)calloc(TempGame->NumPenguins, sizeof(int));
    CounterOfPenguins = choose_penguins(IDPlayer, ListOfPenguins, TempGame);
    ChoosePenguin = ListOfPenguins[rand() % CounterOfPenguins];
    CounterSet = 0;
    Prop = 2;
    MinFish = 3;
    do
    {
        TempNumber = 1;
        while (TempGame->Map[TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionX + TempNumber][TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionY].Fish != 0 && TempNumber != -1)
        {
            if (count_direction(TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionX + TempNumber, TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionY, TempGame) >= Prop && TempGame->Map[TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionX + TempNumber][TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionY].Fish >= MinFish)
            {
                Set[CounterSet][0] = TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionX + TempNumber;
                Set[CounterSet][1] = TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionY;
                TempNumber = -2;
                CounterSet++;
            }
            TempNumber++;
        }
        TempNumber = 1;
        while (TempGame->Map[TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionX - TempNumber][TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionY].Fish != 0 && TempNumber != -1)
        {
            if (count_direction(TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionX - TempNumber, TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionY, TempGame) >= Prop && TempGame->Map[TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionX - TempNumber][TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionY].Fish >= MinFish)
            {
                Set[CounterSet][0] = TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionX - TempNumber;
                Set[CounterSet][1] = TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionY;
                TempNumber = -2;
                CounterSet++;
            }
            TempNumber++;
        }
        TempNumber = 1;
        while (TempGame->Map[TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionX][TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionY + TempNumber].Fish != 0 && TempNumber != -1)
        {
            if (count_direction(TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionX, TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionY + TempNumber, TempGame) >= Prop && TempGame->Map[TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionX][TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionY + TempNumber].Fish >= MinFish)
            {
                Set[CounterSet][0] = TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionX;
                Set[CounterSet][1] = TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionY + TempNumber;
                TempNumber = -2;
                CounterSet++;
            }
            TempNumber++;
        }
        TempNumber = 1;
        while (TempGame->Map[TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionX][TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionY - TempNumber].Fish != 0 && TempNumber != -1)
        {
            if (count_direction(TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionX, TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionY - TempNumber, TempGame) >= Prop && TempGame->Map[TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionX][TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionY - TempNumber].Fish >= MinFish)
            {
                Set[CounterSet][0] = TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionX;
                Set[CounterSet][1] = TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionY - TempNumber;
                TempNumber = -2;
                CounterSet++;
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
    TempNumber = rand() % CounterSet;
    x = Set[TempNumber][0];
    y = Set[TempNumber][1];
    TempGame->Player[IDPlayer].Score = TempGame->Player[IDPlayer].Score + TempGame->Map[x][y].Fish;
    TempGame->Map[x][y].Fish = 0;
    TempGame->Map[x][y].Player = IDPlayer;
    TempGame->Map[x][y].Penguin = ChoosePenguin;
    TempGame->Map[TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionX][TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionY].Player = -1;
    TempGame->Map[TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionX][TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionY].Penguin = -1;
    TempGame->Player[IDPlayer].Penguin[TempGame->Map[x][y].Penguin].PositionX = x;
    TempGame->Player[IDPlayer].Penguin[TempGame->Map[x][y].Penguin].PositionY = y;
    TempGame->Player[IDPlayer].Penguin[TempGame->Map[x][y].Penguin].Movable = check_penguin(x, y, TempGame);
    if (TempGame->Map[x + 1][y].Player != -1)
    {
        TempGame->Player[TempGame->Map[x + 1][y].Player].Penguin[TempGame->Map[x + 1][y].Penguin].Movable = check_penguin(x + 1, y, TempGame);
    }
    if (TempGame->Map[x - 1][y].Player != -1)
    {
        TempGame->Player[TempGame->Map[x - 1][y].Player].Penguin[TempGame->Map[x - 1][y].Penguin].Movable = check_penguin(x - 1, y, TempGame);
    }
    if (TempGame->Map[x][y + 1].Player != -1)
    {
        TempGame->Player[TempGame->Map[x][y + 1].Player].Penguin[TempGame->Map[x][y + 1].Penguin].Movable = check_penguin(x, y + 1, TempGame);
    }
    if (TempGame->Map[x][y - 1].Player != -1)
    {
        TempGame->Player[TempGame->Map[x][y - 1].Player].Penguin[TempGame->Map[x][y - 1].Penguin].Movable = check_penguin(x, y - 1, TempGame);
    }
    if (TempGame->Player[TempGame->NumPlayers - 1].BotNumber != TempGame->NumPlayers)
    {
        print_map(TempGame);
    }
    free(ListOfPenguins);
}
void bot_level_5(int IDPlayer, struct Game *TempGame)
{
    int ChoosePenguin, Set[100][5], CounterSet = 0, TempNumber, x, y, Prop, MinFish, *ListOfPenguins, CounterOfPenguins;
    ListOfPenguins = (int *)calloc(TempGame->NumPenguins, sizeof(int));
    CounterOfPenguins = choose_penguins(IDPlayer, ListOfPenguins, TempGame);
    ChoosePenguin = ListOfPenguins[rand() % CounterOfPenguins];
    CounterSet = 0;
    Set[0][2] = 0;
    Set[0][3] = 0;
    Set[0][4] = 0;
    Prop = 2;
    MinFish = 3;
    do
    {
        TempNumber = 1;
        while (TempGame->Map[TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionX + TempNumber][TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionY].Fish != 0)
        {
            if (count_direction(TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionX + TempNumber, TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionY, TempGame) >= Prop && TempGame->Map[TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionX + TempNumber][TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionY].Fish >= MinFish)
            {
                count_potential(Set[CounterSet], TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionX + TempNumber, TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionY, TempGame);
                if (CounterSet == 0)
                {
                    Set[CounterSet][0] = TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionX + TempNumber;
                    Set[CounterSet][1] = TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionY;
                    CounterSet++;
                }
                else
                {
                    if (compair_potential(Set[CounterSet - 1], Set[CounterSet]) > 0)
                    {
                        Set[0][0] = TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionX + TempNumber;
                        Set[0][1] = TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionY;
                        Set[0][2] = Set[CounterSet][2];
                        Set[0][3] = Set[CounterSet][3];
                        Set[0][4] = Set[CounterSet][4];
                        CounterSet = 1;
                    }
                    else
                    {
                        if (compair_potential(Set[CounterSet - 1], Set[CounterSet]) == 0)
                        {
                            Set[CounterSet][0] = TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionX + TempNumber;
                            Set[CounterSet][1] = TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionY;
                            CounterSet++;
                        }
                    }
                }
            }
            TempNumber++;
        }
        TempNumber = 1;
        while (TempGame->Map[TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionX - TempNumber][TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionY].Fish != 0)
        {
            if (count_direction(TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionX - TempNumber, TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionY, TempGame) >= Prop && TempGame->Map[TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionX - TempNumber][TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionY].Fish >= MinFish)
            {
                count_potential(Set[CounterSet], TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionX - TempNumber, TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionY, TempGame);
                if (CounterSet == 0)
                {
                    Set[CounterSet][0] = TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionX - TempNumber;
                    Set[CounterSet][1] = TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionY;
                    CounterSet++;
                }
                else
                {
                    if (compair_potential(Set[CounterSet - 1], Set[CounterSet]) > 0)
                    {
                        Set[0][0] = TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionX - TempNumber;
                        Set[0][1] = TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionY;
                        Set[0][2] = Set[CounterSet][2];
                        Set[0][3] = Set[CounterSet][3];
                        Set[0][4] = Set[CounterSet][4];
                        CounterSet = 1;
                    }
                    else
                    {
                        if (compair_potential(Set[CounterSet - 1], Set[CounterSet]) == 0)
                        {
                            Set[CounterSet][0] = TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionX - TempNumber;
                            Set[CounterSet][1] = TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionY;
                            CounterSet++;
                        }
                    }
                }
            }
            TempNumber++;
        }
        TempNumber = 1;
        while (TempGame->Map[TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionX][TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionY + TempNumber].Fish != 0)
        {
            if (count_direction(TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionX, TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionY + TempNumber, TempGame) >= Prop && TempGame->Map[TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionX][TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionY + TempNumber].Fish >= MinFish)
            {
                count_potential(Set[CounterSet], TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionX, TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionY + TempNumber, TempGame);
                if (CounterSet == 0)
                {
                    Set[CounterSet][0] = TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionX;
                    Set[CounterSet][1] = TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionY + TempNumber;
                    CounterSet++;
                }
                else
                {
                    if (compair_potential(Set[CounterSet - 1], Set[CounterSet]) > 0)
                    {
                        Set[0][0] = TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionX;
                        Set[0][1] = TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionY + TempNumber;
                        Set[0][2] = Set[CounterSet][2];
                        Set[0][3] = Set[CounterSet][3];
                        Set[0][4] = Set[CounterSet][4];
                        CounterSet = 1;
                    }
                    else
                    {
                        if (compair_potential(Set[CounterSet - 1], Set[CounterSet]) == 0)
                        {
                            Set[CounterSet][0] = TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionX;
                            Set[CounterSet][1] = TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionY + TempNumber;
                            CounterSet++;
                        }
                    }
                }
            }
            TempNumber++;
        }
        TempNumber = 1;
        while (TempGame->Map[TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionX][TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionY - TempNumber].Fish != 0)
        {
            if (count_direction(TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionX, TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionY - TempNumber, TempGame) >= Prop && TempGame->Map[TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionX][TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionY - TempNumber].Fish >= MinFish)
            {
                count_potential(Set[CounterSet], TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionX, TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionY - TempNumber, TempGame);
                if (CounterSet == 0)
                {
                    Set[CounterSet][0] = TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionX;
                    Set[CounterSet][1] = TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionY - TempNumber;
                    CounterSet++;
                }
                else
                {
                    if (compair_potential(Set[CounterSet - 1], Set[CounterSet]) > 0)
                    {
                        Set[0][0] = TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionX;
                        Set[0][1] = TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionY - TempNumber;
                        Set[0][2] = Set[CounterSet][2];
                        Set[0][3] = Set[CounterSet][3];
                        Set[0][4] = Set[CounterSet][4];
                        CounterSet = 1;
                    }
                    else
                    {
                        if (compair_potential(Set[CounterSet - 1], Set[CounterSet]) == 0)
                        {
                            Set[CounterSet][0] = TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionX;
                            Set[CounterSet][1] = TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionY - TempNumber;
                            CounterSet++;
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
    TempNumber = rand() % CounterSet;
    x = Set[TempNumber][0];
    y = Set[TempNumber][1];
    TempGame->Player[IDPlayer].Score = TempGame->Player[IDPlayer].Score + TempGame->Map[x][y].Fish;
    TempGame->Map[x][y].Fish = 0;
    TempGame->Map[x][y].Player = IDPlayer;
    TempGame->Map[x][y].Penguin = ChoosePenguin;
    TempGame->Map[TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionX][TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionY].Player = -1;
    TempGame->Map[TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionX][TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionY].Penguin = -1;
    TempGame->Player[IDPlayer].Penguin[TempGame->Map[x][y].Penguin].PositionX = x;
    TempGame->Player[IDPlayer].Penguin[TempGame->Map[x][y].Penguin].PositionY = y;
    TempGame->Player[IDPlayer].Penguin[TempGame->Map[x][y].Penguin].Movable = check_penguin(x, y, TempGame);
    if (TempGame->Map[x + 1][y].Player != -1)
    {
        TempGame->Player[TempGame->Map[x + 1][y].Player].Penguin[TempGame->Map[x + 1][y].Penguin].Movable = check_penguin(x + 1, y, TempGame);
    }
    if (TempGame->Map[x - 1][y].Player != -1)
    {
        TempGame->Player[TempGame->Map[x - 1][y].Player].Penguin[TempGame->Map[x - 1][y].Penguin].Movable = check_penguin(x - 1, y, TempGame);
    }
    if (TempGame->Map[x][y + 1].Player != -1)
    {
        TempGame->Player[TempGame->Map[x][y + 1].Player].Penguin[TempGame->Map[x][y + 1].Penguin].Movable = check_penguin(x, y + 1, TempGame);
    }
    if (TempGame->Map[x][y - 1].Player != -1)
    {
        TempGame->Player[TempGame->Map[x][y - 1].Player].Penguin[TempGame->Map[x][y - 1].Penguin].Movable = check_penguin(x, y - 1, TempGame);
    }
    if (TempGame->Player[TempGame->NumPlayers - 1].BotNumber != TempGame->NumPlayers)
    {
        print_map(TempGame);
    }
    free(ListOfPenguins);
}
void bot_level_6(int IDPlayer, struct Game *TempGame)
{
    int ChoosePenguin, Set[100][6], CounterSet = 0, TempNumber, x, y, Prop, MinFish, *ListOfPenguins, CounterOfPenguins;
    ListOfPenguins = (int *)calloc(TempGame->NumPenguins, sizeof(int));
    CounterOfPenguins = choose_penguins(IDPlayer, ListOfPenguins, TempGame);
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
        while (TempGame->Map[TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionX + TempNumber][TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionY].Fish != 0)
        {
            if (count_direction(TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionX + TempNumber, TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionY, TempGame) >= Prop && TempGame->Map[TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionX + TempNumber][TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionY].Fish >= MinFish)
            {
                count_potential(Set[CounterSet], TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionX + TempNumber, TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionY, TempGame);
                if (CounterSet == 0)
                {
                    Set[CounterSet][0] = TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionX + TempNumber;
                    Set[CounterSet][1] = TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionY;
                    Set[CounterSet][5] = TempNumber;
                    CounterSet++;
                }
                else
                {
                    if (compair_potential(Set[CounterSet - 1], Set[CounterSet]) > 0)
                    {
                        Set[0][0] = TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionX + TempNumber;
                        Set[0][1] = TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionY;
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
                            Set[0][0] = TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionX + TempNumber;
                            Set[0][1] = TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionY;
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
        while (TempGame->Map[TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionX - TempNumber][TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionY].Fish != 0)
        {
            if (count_direction(TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionX - TempNumber, TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionY, TempGame) >= Prop && TempGame->Map[TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionX - TempNumber][TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionY].Fish >= MinFish)
            {
                count_potential(Set[CounterSet], TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionX - TempNumber, TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionY, TempGame);
                if (CounterSet == 0)
                {
                    Set[CounterSet][0] = TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionX - TempNumber;
                    Set[CounterSet][1] = TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionY;
                    CounterSet++;
                }
                else
                {
                    if (compair_potential(Set[CounterSet - 1], Set[CounterSet]) > 0)
                    {
                        Set[0][0] = TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionX - TempNumber;
                        Set[0][1] = TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionY;
                        Set[0][2] = Set[CounterSet][2];
                        Set[0][3] = Set[CounterSet][3];
                        Set[0][4] = Set[CounterSet][4];
                        CounterSet = 1;
                    }
                    else
                    {
                        if (compair_potential(Set[CounterSet - 1], Set[CounterSet]) == 0 && Set[CounterSet - 1][5] > TempNumber)
                        {
                            Set[0][0] = TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionX - TempNumber;
                            Set[0][1] = TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionY;
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
        while (TempGame->Map[TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionX][TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionY + TempNumber].Fish != 0)
        {
            if (count_direction(TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionX, TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionY + TempNumber, TempGame) >= Prop && TempGame->Map[TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionX][TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionY + TempNumber].Fish >= MinFish)
            {
                count_potential(Set[CounterSet], TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionX, TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionY + TempNumber, TempGame);
                if (CounterSet == 0)
                {
                    Set[CounterSet][0] = TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionX;
                    Set[CounterSet][1] = TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionY + TempNumber;
                    CounterSet++;
                }
                else
                {
                    if (compair_potential(Set[CounterSet - 1], Set[CounterSet]) > 0)
                    {
                        Set[0][0] = TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionX;
                        Set[0][1] = TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionY + TempNumber;
                        Set[0][2] = Set[CounterSet][2];
                        Set[0][3] = Set[CounterSet][3];
                        Set[0][4] = Set[CounterSet][4];
                        CounterSet = 1;
                    }
                    else
                    {
                        if (compair_potential(Set[CounterSet - 1], Set[CounterSet]) == 0 && Set[CounterSet - 1][5] > TempNumber)
                        {
                            Set[0][0] = TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionX;
                            Set[0][1] = TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionY + TempNumber;
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
        while (TempGame->Map[TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionX][TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionY - TempNumber].Fish != 0)
        {
            if (count_direction(TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionX, TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionY - TempNumber, TempGame) >= Prop && TempGame->Map[TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionX][TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionY - TempNumber].Fish >= MinFish)
            {
                count_potential(Set[CounterSet], TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionX, TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionY - TempNumber, TempGame);
                if (CounterSet == 0)
                {
                    Set[CounterSet][0] = TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionX;
                    Set[CounterSet][1] = TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionY - TempNumber;
                    CounterSet++;
                }
                else
                {
                    if (compair_potential(Set[CounterSet - 1], Set[CounterSet]) > 0)
                    {
                        Set[0][0] = TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionX;
                        Set[0][1] = TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionY - TempNumber;
                        Set[0][2] = Set[CounterSet][2];
                        Set[0][3] = Set[CounterSet][3];
                        Set[0][4] = Set[CounterSet][4];
                        CounterSet = 1;
                    }
                    else
                    {
                        if (compair_potential(Set[CounterSet - 1], Set[CounterSet]) == 0 && Set[CounterSet - 1][5] > TempNumber)
                        {
                            Set[0][0] = TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionX;
                            Set[0][1] = TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionY - TempNumber;
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
    TempGame->Player[IDPlayer].Score = TempGame->Player[IDPlayer].Score + TempGame->Map[x][y].Fish;
    TempGame->Map[x][y].Fish = 0;
    TempGame->Map[x][y].Player = IDPlayer;
    TempGame->Map[x][y].Penguin = ChoosePenguin;
    TempGame->Map[TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionX][TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionY].Player = -1;
    TempGame->Map[TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionX][TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionY].Penguin = -1;
    TempGame->Player[IDPlayer].Penguin[TempGame->Map[x][y].Penguin].PositionX = x;
    TempGame->Player[IDPlayer].Penguin[TempGame->Map[x][y].Penguin].PositionY = y;
    TempGame->Player[IDPlayer].Penguin[TempGame->Map[x][y].Penguin].Movable = check_penguin(x, y, TempGame);
    if (TempGame->Map[x + 1][y].Player != -1)
    {
        TempGame->Player[TempGame->Map[x + 1][y].Player].Penguin[TempGame->Map[x + 1][y].Penguin].Movable = check_penguin(x + 1, y, TempGame);
    }
    if (TempGame->Map[x - 1][y].Player != -1)
    {
        TempGame->Player[TempGame->Map[x - 1][y].Player].Penguin[TempGame->Map[x - 1][y].Penguin].Movable = check_penguin(x - 1, y, TempGame);
    }
    if (TempGame->Map[x][y + 1].Player != -1)
    {
        TempGame->Player[TempGame->Map[x][y + 1].Player].Penguin[TempGame->Map[x][y + 1].Penguin].Movable = check_penguin(x, y + 1, TempGame);
    }
    if (TempGame->Map[x][y - 1].Player != -1)
    {
        TempGame->Player[TempGame->Map[x][y - 1].Player].Penguin[TempGame->Map[x][y - 1].Penguin].Movable = check_penguin(x, y - 1, TempGame);
    }
    if (TempGame->Player[TempGame->NumPlayers - 1].BotNumber != TempGame->NumPlayers)
    {
        print_map(TempGame);
    }
    free(ListOfPenguins);
}
void bot_level_7(int IDPlayer, struct Game *TempGame)
{
    int ChoosePenguin, Set[100][5], CounterSet = 0, TempNumber, x, y, Prop, MinFish, *ListOfPenguins, CounterOfPenguins;
    ListOfPenguins = (int *)calloc(TempGame->NumPenguins, sizeof(int));
    CounterOfPenguins = choose_penguins(IDPlayer, ListOfPenguins, TempGame);
    ChoosePenguin = ListOfPenguins[rand() % CounterOfPenguins];
    CounterSet = 0;
    Set[0][2] = 0;
    Set[0][3] = 0;
    Set[0][4] = 0;
    Prop = 2;
    MinFish = 3;
    do
    {
        TempNumber = 1;
        while (TempGame->Map[TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionX + TempNumber][TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionY].Fish != 0)
        {
            if (count_direction(TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionX + TempNumber, TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionY, TempGame) >= Prop && TempGame->Map[TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionX + TempNumber][TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionY].Fish >= MinFish)
            {
                count_potential(Set[CounterSet], TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionX + TempNumber, TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionY, TempGame);
                if (CounterSet == 0)
                {
                    Set[CounterSet][0] = TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionX + TempNumber;
                    Set[CounterSet][1] = TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionY;
                    CounterSet++;
                }
                else
                {
                    if (compair_potential_Vers_II(Set[CounterSet - 1], Set[CounterSet]) > 0)
                    {
                        Set[0][0] = TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionX + TempNumber;
                        Set[0][1] = TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionY;
                        Set[0][2] = Set[CounterSet][2];
                        Set[0][3] = Set[CounterSet][3];
                        Set[0][4] = Set[CounterSet][4];
                        CounterSet = 1;
                    }
                    else
                    {
                        if (compair_potential_Vers_II(Set[CounterSet - 1], Set[CounterSet]) == 0)
                        {
                            Set[CounterSet][0] = TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionX + TempNumber;
                            Set[CounterSet][1] = TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionY;
                            CounterSet++;
                        }
                    }
                }
            }
            TempNumber++;
        }
        TempNumber = 1;
        while (TempGame->Map[TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionX - TempNumber][TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionY].Fish != 0)
        {
            if (count_direction(TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionX - TempNumber, TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionY, TempGame) >= Prop && TempGame->Map[TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionX - TempNumber][TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionY].Fish >= MinFish)
            {
                count_potential(Set[CounterSet], TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionX - TempNumber, TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionY, TempGame);
                if (CounterSet == 0)
                {
                    Set[CounterSet][0] = TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionX - TempNumber;
                    Set[CounterSet][1] = TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionY;
                    CounterSet++;
                }
                else
                {
                    if (compair_potential_Vers_II(Set[CounterSet - 1], Set[CounterSet]) > 0)
                    {
                        Set[0][0] = TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionX - TempNumber;
                        Set[0][1] = TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionY;
                        Set[0][2] = Set[CounterSet][2];
                        Set[0][3] = Set[CounterSet][3];
                        Set[0][4] = Set[CounterSet][4];
                        CounterSet = 1;
                    }
                    else
                    {
                        if (compair_potential_Vers_II(Set[CounterSet - 1], Set[CounterSet]) == 0)
                        {
                            Set[CounterSet][0] = TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionX - TempNumber;
                            Set[CounterSet][1] = TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionY;
                            CounterSet++;
                        }
                    }
                }
            }
            TempNumber++;
        }
        TempNumber = 1;
        while (TempGame->Map[TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionX][TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionY + TempNumber].Fish != 0)
        {
            if (count_direction(TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionX, TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionY + TempNumber, TempGame) >= Prop && TempGame->Map[TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionX][TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionY + TempNumber].Fish >= MinFish)
            {
                count_potential(Set[CounterSet], TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionX, TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionY + TempNumber, TempGame);
                if (CounterSet == 0)
                {
                    Set[CounterSet][0] = TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionX;
                    Set[CounterSet][1] = TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionY + TempNumber;
                    CounterSet++;
                }
                else
                {
                    if (compair_potential_Vers_II(Set[CounterSet - 1], Set[CounterSet]) > 0)
                    {
                        Set[0][0] = TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionX;
                        Set[0][1] = TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionY + TempNumber;
                        Set[0][2] = Set[CounterSet][2];
                        Set[0][3] = Set[CounterSet][3];
                        Set[0][4] = Set[CounterSet][4];
                        CounterSet = 1;
                    }
                    else
                    {
                        if (compair_potential_Vers_II(Set[CounterSet - 1], Set[CounterSet]) == 0)
                        {
                            Set[CounterSet][0] = TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionX;
                            Set[CounterSet][1] = TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionY + TempNumber;
                            CounterSet++;
                        }
                    }
                }
            }
            TempNumber++;
        }
        TempNumber = 1;
        while (TempGame->Map[TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionX][TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionY - TempNumber].Fish != 0)
        {
            if (count_direction(TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionX, TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionY - TempNumber, TempGame) >= Prop && TempGame->Map[TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionX][TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionY - TempNumber].Fish >= MinFish)
            {
                count_potential(Set[CounterSet], TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionX, TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionY - TempNumber, TempGame);
                if (CounterSet == 0)
                {
                    Set[CounterSet][0] = TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionX;
                    Set[CounterSet][1] = TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionY - TempNumber;
                    CounterSet++;
                }
                else
                {
                    if (compair_potential_Vers_II(Set[CounterSet - 1], Set[CounterSet]) > 0)
                    {
                        Set[0][0] = TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionX;
                        Set[0][1] = TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionY - TempNumber;
                        Set[0][2] = Set[CounterSet][2];
                        Set[0][3] = Set[CounterSet][3];
                        Set[0][4] = Set[CounterSet][4];
                        CounterSet = 1;
                    }
                    else
                    {
                        if (compair_potential_Vers_II(Set[CounterSet - 1], Set[CounterSet]) == 0)
                        {
                            Set[CounterSet][0] = TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionX;
                            Set[CounterSet][1] = TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionY - TempNumber;
                            CounterSet++;
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
    TempNumber = rand() % CounterSet;
    x = Set[TempNumber][0];
    y = Set[TempNumber][1];
    TempGame->Player[IDPlayer].Score = TempGame->Player[IDPlayer].Score + TempGame->Map[x][y].Fish;
    TempGame->Map[x][y].Fish = 0;
    TempGame->Map[x][y].Player = IDPlayer;
    TempGame->Map[x][y].Penguin = ChoosePenguin;
    TempGame->Map[TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionX][TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionY].Player = -1;
    TempGame->Map[TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionX][TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionY].Penguin = -1;
    TempGame->Player[IDPlayer].Penguin[TempGame->Map[x][y].Penguin].PositionX = x;
    TempGame->Player[IDPlayer].Penguin[TempGame->Map[x][y].Penguin].PositionY = y;
    TempGame->Player[IDPlayer].Penguin[TempGame->Map[x][y].Penguin].Movable = check_penguin(x, y, TempGame);
    if (TempGame->Map[x + 1][y].Player != -1)
    {
        TempGame->Player[TempGame->Map[x + 1][y].Player].Penguin[TempGame->Map[x + 1][y].Penguin].Movable = check_penguin(x + 1, y, TempGame);
    }
    if (TempGame->Map[x - 1][y].Player != -1)
    {
        TempGame->Player[TempGame->Map[x - 1][y].Player].Penguin[TempGame->Map[x - 1][y].Penguin].Movable = check_penguin(x - 1, y, TempGame);
    }
    if (TempGame->Map[x][y + 1].Player != -1)
    {
        TempGame->Player[TempGame->Map[x][y + 1].Player].Penguin[TempGame->Map[x][y + 1].Penguin].Movable = check_penguin(x, y + 1, TempGame);
    }
    if (TempGame->Map[x][y - 1].Player != -1)
    {
        TempGame->Player[TempGame->Map[x][y - 1].Player].Penguin[TempGame->Map[x][y - 1].Penguin].Movable = check_penguin(x, y - 1, TempGame);
    }
    if (TempGame->Player[TempGame->NumPlayers - 1].BotNumber != TempGame->NumPlayers)
    {
        print_map(TempGame);
    }
    free(ListOfPenguins);
}
void bot_level_8(int IDPlayer, struct Game *TempGame)
{
    int ChoosePenguin, Set[100][6], CounterSet = 0, TempNumber, x, y, Prop, MinFish, *ListOfPenguins, CounterOfPenguins;
    ListOfPenguins = (int *)calloc(TempGame->NumPenguins, sizeof(int));
    CounterOfPenguins = choose_penguins(IDPlayer, ListOfPenguins, TempGame);
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
        while (TempGame->Map[TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionX + TempNumber][TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionY].Fish != 0)
        {
            if (count_direction(TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionX + TempNumber, TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionY, TempGame) >= Prop && TempGame->Map[TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionX + TempNumber][TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionY].Fish >= MinFish)
            {
                count_potential(Set[CounterSet], TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionX + TempNumber, TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionY, TempGame);
                if (CounterSet == 0)
                {
                    Set[CounterSet][0] = TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionX + TempNumber;
                    Set[CounterSet][1] = TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionY;
                    Set[CounterSet][5] = TempNumber;
                    CounterSet++;
                }
                else
                {
                    if (compair_potential_Vers_II(Set[CounterSet - 1], Set[CounterSet]) > 0)
                    {
                        Set[0][0] = TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionX + TempNumber;
                        Set[0][1] = TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionY;
                        Set[0][2] = Set[CounterSet][2];
                        Set[0][3] = Set[CounterSet][3];
                        Set[0][4] = Set[CounterSet][4];
                        Set[0][5] = TempNumber;
                        CounterSet = 1;
                    }
                    else
                    {
                        if (compair_potential_Vers_II(Set[CounterSet - 1], Set[CounterSet]) == 0 && Set[CounterSet - 1][5] > TempNumber)
                        {
                            Set[0][0] = TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionX + TempNumber;
                            Set[0][1] = TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionY;
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
        while (TempGame->Map[TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionX - TempNumber][TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionY].Fish != 0)
        {
            if (count_direction(TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionX - TempNumber, TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionY, TempGame) >= Prop && TempGame->Map[TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionX - TempNumber][TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionY].Fish >= MinFish)
            {
                count_potential(Set[CounterSet], TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionX - TempNumber, TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionY, TempGame);
                if (CounterSet == 0)
                {
                    Set[CounterSet][0] = TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionX - TempNumber;
                    Set[CounterSet][1] = TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionY;
                    CounterSet++;
                }
                else
                {
                    if (compair_potential_Vers_II(Set[CounterSet - 1], Set[CounterSet]) > 0)
                    {
                        Set[0][0] = TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionX - TempNumber;
                        Set[0][1] = TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionY;
                        Set[0][2] = Set[CounterSet][2];
                        Set[0][3] = Set[CounterSet][3];
                        Set[0][4] = Set[CounterSet][4];
                        CounterSet = 1;
                    }
                    else
                    {
                        if (compair_potential_Vers_II(Set[CounterSet - 1], Set[CounterSet]) == 0 && Set[CounterSet - 1][5] > TempNumber)
                        {
                            Set[0][0] = TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionX - TempNumber;
                            Set[0][1] = TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionY;
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
        while (TempGame->Map[TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionX][TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionY + TempNumber].Fish != 0)
        {
            if (count_direction(TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionX, TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionY + TempNumber, TempGame) >= Prop && TempGame->Map[TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionX][TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionY + TempNumber].Fish >= MinFish)
            {
                count_potential(Set[CounterSet], TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionX, TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionY + TempNumber, TempGame);
                if (CounterSet == 0)
                {
                    Set[CounterSet][0] = TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionX;
                    Set[CounterSet][1] = TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionY + TempNumber;
                    CounterSet++;
                }
                else
                {
                    if (compair_potential_Vers_II(Set[CounterSet - 1], Set[CounterSet]) > 0)
                    {
                        Set[0][0] = TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionX;
                        Set[0][1] = TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionY + TempNumber;
                        Set[0][2] = Set[CounterSet][2];
                        Set[0][3] = Set[CounterSet][3];
                        Set[0][4] = Set[CounterSet][4];
                        CounterSet = 1;
                    }
                    else
                    {
                        if (compair_potential_Vers_II(Set[CounterSet - 1], Set[CounterSet]) == 0 && Set[CounterSet - 1][5] > TempNumber)
                        {
                            Set[0][0] = TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionX;
                            Set[0][1] = TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionY + TempNumber;
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
        while (TempGame->Map[TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionX][TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionY - TempNumber].Fish != 0)
        {
            if (count_direction(TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionX, TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionY - TempNumber, TempGame) >= Prop && TempGame->Map[TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionX][TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionY - TempNumber].Fish >= MinFish)
            {
                count_potential(Set[CounterSet], TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionX, TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionY - TempNumber, TempGame);
                if (CounterSet == 0)
                {
                    Set[CounterSet][0] = TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionX;
                    Set[CounterSet][1] = TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionY - TempNumber;
                    CounterSet++;
                }
                else
                {
                    if (compair_potential_Vers_II(Set[CounterSet - 1], Set[CounterSet]) > 0)
                    {
                        Set[0][0] = TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionX;
                        Set[0][1] = TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionY - TempNumber;
                        Set[0][2] = Set[CounterSet][2];
                        Set[0][3] = Set[CounterSet][3];
                        Set[0][4] = Set[CounterSet][4];
                        CounterSet = 1;
                    }
                    else
                    {
                        if (compair_potential_Vers_II(Set[CounterSet - 1], Set[CounterSet]) == 0 && Set[CounterSet - 1][5] > TempNumber)
                        {
                            Set[0][0] = TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionX;
                            Set[0][1] = TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionY - TempNumber;
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
    TempGame->Player[IDPlayer].Score = TempGame->Player[IDPlayer].Score + TempGame->Map[x][y].Fish;
    TempGame->Map[x][y].Fish = 0;
    TempGame->Map[x][y].Player = IDPlayer;
    TempGame->Map[x][y].Penguin = ChoosePenguin;
    TempGame->Map[TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionX][TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionY].Player = -1;
    TempGame->Map[TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionX][TempGame->Player[IDPlayer].Penguin[ChoosePenguin].PositionY].Penguin = -1;
    TempGame->Player[IDPlayer].Penguin[TempGame->Map[x][y].Penguin].PositionX = x;
    TempGame->Player[IDPlayer].Penguin[TempGame->Map[x][y].Penguin].PositionY = y;
    TempGame->Player[IDPlayer].Penguin[TempGame->Map[x][y].Penguin].Movable = check_penguin(x, y, TempGame);
    if (TempGame->Map[x + 1][y].Player != -1)
    {
        TempGame->Player[TempGame->Map[x + 1][y].Player].Penguin[TempGame->Map[x + 1][y].Penguin].Movable = check_penguin(x + 1, y, TempGame);
    }
    if (TempGame->Map[x - 1][y].Player != -1)
    {
        TempGame->Player[TempGame->Map[x - 1][y].Player].Penguin[TempGame->Map[x - 1][y].Penguin].Movable = check_penguin(x - 1, y, TempGame);
    }
    if (TempGame->Map[x][y + 1].Player != -1)
    {
        TempGame->Player[TempGame->Map[x][y + 1].Player].Penguin[TempGame->Map[x][y + 1].Penguin].Movable = check_penguin(x, y + 1, TempGame);
    }
    if (TempGame->Map[x][y - 1].Player != -1)
    {
        TempGame->Player[TempGame->Map[x][y - 1].Player].Penguin[TempGame->Map[x][y - 1].Penguin].Movable = check_penguin(x, y - 1, TempGame);
    }
    if (TempGame->Player[TempGame->NumPlayers - 1].BotNumber != TempGame->NumPlayers)
    {
        print_map(TempGame);
    }
    free(ListOfPenguins);
}
void bot_put_penguin(int IDPlayer, int IDPenguin, struct Game *TempGame)
{
    switch (TempGame->Player[IDPlayer].Bot)
    {
    case 1:
        random_put_penguin(IDPlayer, IDPenguin, TempGame);
        break;
    case 2:
        random_put_penguin(IDPlayer, IDPenguin, TempGame);
        break;
    case 3:
        random_put_penguin(IDPlayer, IDPenguin, TempGame);
        break;
    case 4:
        random_put_penguin(IDPlayer, IDPenguin, TempGame);
        break;
    case 5:
        put_penguin_with_potential(IDPlayer, IDPenguin, TempGame);
        break;
    case 6:
        put_penguin_with_potential(IDPlayer, IDPenguin, TempGame);
        break;
    case 7:
        put_penguin_with_potential_Vers_II(IDPlayer, IDPenguin, TempGame);
        break;
    case 8:
        put_penguin_with_potential_Vers_II(IDPlayer, IDPenguin, TempGame);
        break;
    }
}
void bot_turn(int IDPlayer, struct Game *TempGame)
{
    switch (TempGame->Player[IDPlayer].Bot)
    {
    case 1:
        bot_level_1(IDPlayer, TempGame);
        break;
    case 2:
        bot_level_2(IDPlayer, TempGame);
        break;
    case 3:
        bot_level_3(IDPlayer, TempGame);
        break;
    case 4:
        bot_level_4(IDPlayer, TempGame);
        break;
    case 5:
        bot_level_5(IDPlayer, TempGame);
        break;
    case 6:
        bot_level_6(IDPlayer, TempGame);
        break;
    case 7:
        bot_level_7(IDPlayer, TempGame);
        break;
    case 8:
        bot_level_8(IDPlayer, TempGame);
        break;
    }
}