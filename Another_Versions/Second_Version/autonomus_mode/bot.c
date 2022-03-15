int choose_penguins(int *ListOfPenguins, struct Game *Game)
{
    int NumberOfSide, CounterOfPenguins = 0;
    for (int i = 0; i < Game->Player[Game->MyNumber].NumberOfPenguins; i++)
    {
        NumberOfSide = 4;
        if (Game->Map[Game->Player[Game->MyNumber].Penguin[i].PositionX + 1][Game->Player[Game->MyNumber].Penguin[i].PositionY].Fish == 0 || Game->Map[Game->Player[Game->MyNumber].Penguin[i].PositionX + 1][Game->Player[Game->MyNumber].Penguin[i].PositionY].Player != -1)
        {
            NumberOfSide--;
        }
        if (Game->Map[Game->Player[Game->MyNumber].Penguin[i].PositionX - 1][Game->Player[Game->MyNumber].Penguin[i].PositionY].Fish == 0 || Game->Map[Game->Player[Game->MyNumber].Penguin[i].PositionX - 1][Game->Player[Game->MyNumber].Penguin[i].PositionY].Player != -1)
        {
            NumberOfSide--;
        }
        if (Game->Map[Game->Player[Game->MyNumber].Penguin[i].PositionX][Game->Player[Game->MyNumber].Penguin[i].PositionY + 1].Fish == 0 || Game->Map[Game->Player[Game->MyNumber].Penguin[i].PositionX][Game->Player[Game->MyNumber].Penguin[i].PositionY + 1].Player != -1)
        {
            NumberOfSide--;
        }
        if (Game->Map[Game->Player[Game->MyNumber].Penguin[i].PositionX][Game->Player[Game->MyNumber].Penguin[i].PositionY - 1].Fish == 0 || Game->Map[Game->Player[Game->MyNumber].Penguin[i].PositionX][Game->Player[Game->MyNumber].Penguin[i].PositionY - 1].Player != -1)
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
        for (int i = 0; i < Game->Player[Game->MyNumber].NumberOfPenguins; i++)
        {
            if (Game->Player[Game->MyNumber].Penguin[i].Movable == 0)
            {
                ListOfPenguins[CounterOfPenguins] = i;
                CounterOfPenguins++;
            }
        }
    }
    return CounterOfPenguins;
}
int count_direction(int x, int y, struct Game *Game)
{
    int Counter = 0;
    if (Game->Map[x][y - 1].Fish != 0 && Game->Map[x][y - 1].Player == -1)
    {
        Counter++;
    }
    if (Game->Map[x][y + 1].Fish != 0 && Game->Map[x][y + 1].Player == -1)
    {
        Counter++;
    }
    if (Game->Map[x + 1][y].Fish != 0 && Game->Map[x + 1][y].Player == -1)
    {
        Counter++;
    }
    if (Game->Map[x - 1][y].Fish != 0 && Game->Map[x - 1][y].Player == -1)
    {
        Counter++;
    }
    return Counter;
}
void count_potential(int *Potential, int X, int Y, struct Game *Game)
{
    Potential[4] = 0;
    Potential[3] = 0;
    Potential[2] = 0;
    int Number = 1;
    while (Game->Map[X + Number][Y].Fish != 0 && Game->Map[X + Number][Y].Player == -1)
    {
        Potential[Game->Map[X + Number][Y].Fish + 1]++;
        Number++;
    }
    Number = 1;
    while (Game->Map[X - Number][Y].Fish != 0 && Game->Map[X - Number][Y].Player == -1)
    {
        Potential[Game->Map[X - Number][Y].Fish + 1]++;
        Number++;
    }
    Number = 1;
    while (Game->Map[X][Y + Number].Fish != 0 && Game->Map[X][Y + Number].Player == -1)
    {
        Potential[Game->Map[X][Y + Number].Fish + 1]++;
        Number++;
    }
    Number = 1;
    while (Game->Map[X][Y - Number].Fish != 0 && Game->Map[X][Y - Number].Player == -1)
    {
        Potential[Game->Map[X][Y - Number].Fish + 1]++;
        Number++;
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
void find_all_cells_with_1(struct Game *Game, int (*CellWith1)[4], int *CountCell)
{
    CountCell[0] = 0;
    CountCell[1] = 0;
    for (int x = 0; x < Game->SizeMapX + 2; x++)
    {
        for (int y = 0; y < Game->SizeMapY + 2; y++)
        {
            if (Game->Map[x][y].Fish == 1 && Game->Map[x][y].Player == -1)
            {
                if (x == 1 || y == 1 || x == Game->SizeMapX || y == Game->SizeMapY)
                {
                    CellWith1[CountCell[1]][2] = x;
                    CellWith1[CountCell[1]][3] = y;
                    CountCell[1]++;
                }
                else
                {
                    CellWith1[CountCell[0]][0] = x;
                    CellWith1[CountCell[0]][1] = y;
                    CountCell[0]++;
                }
            }
        }
    }
}
int bot_put_penguin(struct Game *Game)
{
    int CellWith1[10000][4], Set[100][6], CounterSet = 0, NumberCellWith1[2], x, y, RandomNumber;
    Set[0][2] = 0;
    Set[0][3] = 0;
    Set[0][4] = 0;
    find_all_cells_with_1(Game, CellWith1, NumberCellWith1);
    if (NumberCellWith1[0] == 0 && NumberCellWith1[1] == 0)
    {
        return 1;
    }
    if (NumberCellWith1[0] > 0)
    {
        for (int i = 0; i < NumberCellWith1[0]; i++)
        {
            count_potential(Set[CounterSet], CellWith1[i][0], CellWith1[i][1], Game);
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
            count_potential(Set[CounterSet], CellWith1[i][2], CellWith1[i][3], Game);
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
    if (Game->MyNumber != -1)
    {
        Game->Map[x][y].Player = Game->MyNumber;
        Game->Player[Game->MyNumber].Score += Game->Map[x][y].Fish;
        Game->Player[Game->MyNumber].NumberOfPenguins++;
    }
    else
    {
        Game->Map[x][y].Player = Game->NumPlayers;
    }
    return 0;
}
void bot_make_turn(struct Game *Game)
{
    int ChoosePenguin, Set[100][6], CounterSet = 0, Number, x, y, Prop, MinFish, *ListOfPenguins, CounterOfPenguins;
    ListOfPenguins = (int *)calloc(Game->NumPenguins, sizeof(int));
    CounterOfPenguins = choose_penguins(ListOfPenguins, Game);
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
        Number = 1;
        while (Game->Map[Game->Player[Game->MyNumber].Penguin[ChoosePenguin].PositionX + Number][Game->Player[Game->MyNumber].Penguin[ChoosePenguin].PositionY].Fish != 0 && Game->Map[Game->Player[Game->MyNumber].Penguin[ChoosePenguin].PositionX + Number][Game->Player[Game->MyNumber].Penguin[ChoosePenguin].PositionY].Player == -1)
        {
            if (count_direction(Game->Player[Game->MyNumber].Penguin[ChoosePenguin].PositionX + Number, Game->Player[Game->MyNumber].Penguin[ChoosePenguin].PositionY, Game) >= Prop && Game->Map[Game->Player[Game->MyNumber].Penguin[ChoosePenguin].PositionX + Number][Game->Player[Game->MyNumber].Penguin[ChoosePenguin].PositionY].Fish >= MinFish)
            {
                count_potential(Set[CounterSet], Game->Player[Game->MyNumber].Penguin[ChoosePenguin].PositionX + Number, Game->Player[Game->MyNumber].Penguin[ChoosePenguin].PositionY, Game);
                if (CounterSet == 0)
                {
                    Set[CounterSet][0] = Game->Player[Game->MyNumber].Penguin[ChoosePenguin].PositionX + Number;
                    Set[CounterSet][1] = Game->Player[Game->MyNumber].Penguin[ChoosePenguin].PositionY;
                    Set[CounterSet][5] = Number;
                    CounterSet++;
                }
                else
                {
                    if (compair_potential(Set[CounterSet - 1], Set[CounterSet]) > 0)
                    {
                        Set[0][0] = Game->Player[Game->MyNumber].Penguin[ChoosePenguin].PositionX + Number;
                        Set[0][1] = Game->Player[Game->MyNumber].Penguin[ChoosePenguin].PositionY;
                        Set[0][2] = Set[CounterSet][2];
                        Set[0][3] = Set[CounterSet][3];
                        Set[0][4] = Set[CounterSet][4];
                        Set[0][5] = Number;
                        CounterSet = 1;
                    }
                    else
                    {
                        if (compair_potential(Set[CounterSet - 1], Set[CounterSet]) == 0 && Set[CounterSet - 1][5] > Number)
                        {
                            Set[0][0] = Game->Player[Game->MyNumber].Penguin[ChoosePenguin].PositionX + Number;
                            Set[0][1] = Game->Player[Game->MyNumber].Penguin[ChoosePenguin].PositionY;
                            Set[0][2] = Set[CounterSet][2];
                            Set[0][3] = Set[CounterSet][3];
                            Set[0][4] = Set[CounterSet][4];
                            Set[0][5] = Number;
                            CounterSet = 1;
                        }
                    }
                }
            }
            Number++;
        }
        Number = 1;
        while (Game->Map[Game->Player[Game->MyNumber].Penguin[ChoosePenguin].PositionX - Number][Game->Player[Game->MyNumber].Penguin[ChoosePenguin].PositionY].Fish != 0 && Game->Map[Game->Player[Game->MyNumber].Penguin[ChoosePenguin].PositionX - Number][Game->Player[Game->MyNumber].Penguin[ChoosePenguin].PositionY].Player == -1)
        {
            if (count_direction(Game->Player[Game->MyNumber].Penguin[ChoosePenguin].PositionX - Number, Game->Player[Game->MyNumber].Penguin[ChoosePenguin].PositionY, Game) >= Prop && Game->Map[Game->Player[Game->MyNumber].Penguin[ChoosePenguin].PositionX - Number][Game->Player[Game->MyNumber].Penguin[ChoosePenguin].PositionY].Fish >= MinFish)
            {
                count_potential(Set[CounterSet], Game->Player[Game->MyNumber].Penguin[ChoosePenguin].PositionX - Number, Game->Player[Game->MyNumber].Penguin[ChoosePenguin].PositionY, Game);
                if (CounterSet == 0)
                {
                    Set[CounterSet][0] = Game->Player[Game->MyNumber].Penguin[ChoosePenguin].PositionX - Number;
                    Set[CounterSet][1] = Game->Player[Game->MyNumber].Penguin[ChoosePenguin].PositionY;
                    CounterSet++;
                }
                else
                {
                    if (compair_potential(Set[CounterSet - 1], Set[CounterSet]) > 0)
                    {
                        Set[0][0] = Game->Player[Game->MyNumber].Penguin[ChoosePenguin].PositionX - Number;
                        Set[0][1] = Game->Player[Game->MyNumber].Penguin[ChoosePenguin].PositionY;
                        Set[0][2] = Set[CounterSet][2];
                        Set[0][3] = Set[CounterSet][3];
                        Set[0][4] = Set[CounterSet][4];
                        CounterSet = 1;
                    }
                    else
                    {
                        if (compair_potential(Set[CounterSet - 1], Set[CounterSet]) == 0 && Set[CounterSet - 1][5] > Number)
                        {
                            Set[0][0] = Game->Player[Game->MyNumber].Penguin[ChoosePenguin].PositionX - Number;
                            Set[0][1] = Game->Player[Game->MyNumber].Penguin[ChoosePenguin].PositionY;
                            Set[0][2] = Set[CounterSet][2];
                            Set[0][3] = Set[CounterSet][3];
                            Set[0][4] = Set[CounterSet][4];
                            Set[0][5] = Number;
                            CounterSet = 1;
                        }
                    }
                }
            }
            Number++;
        }
        Number = 1;
        while (Game->Map[Game->Player[Game->MyNumber].Penguin[ChoosePenguin].PositionX][Game->Player[Game->MyNumber].Penguin[ChoosePenguin].PositionY + Number].Fish != 0 && Game->Map[Game->Player[Game->MyNumber].Penguin[ChoosePenguin].PositionX][Game->Player[Game->MyNumber].Penguin[ChoosePenguin].PositionY + Number].Player == -1)
        {
            if (count_direction(Game->Player[Game->MyNumber].Penguin[ChoosePenguin].PositionX, Game->Player[Game->MyNumber].Penguin[ChoosePenguin].PositionY + Number, Game) >= Prop && Game->Map[Game->Player[Game->MyNumber].Penguin[ChoosePenguin].PositionX][Game->Player[Game->MyNumber].Penguin[ChoosePenguin].PositionY + Number].Fish >= MinFish)
            {
                count_potential(Set[CounterSet], Game->Player[Game->MyNumber].Penguin[ChoosePenguin].PositionX, Game->Player[Game->MyNumber].Penguin[ChoosePenguin].PositionY + Number, Game);
                if (CounterSet == 0)
                {
                    Set[CounterSet][0] = Game->Player[Game->MyNumber].Penguin[ChoosePenguin].PositionX;
                    Set[CounterSet][1] = Game->Player[Game->MyNumber].Penguin[ChoosePenguin].PositionY + Number;
                    CounterSet++;
                }
                else
                {
                    if (compair_potential(Set[CounterSet - 1], Set[CounterSet]) > 0)
                    {
                        Set[0][0] = Game->Player[Game->MyNumber].Penguin[ChoosePenguin].PositionX;
                        Set[0][1] = Game->Player[Game->MyNumber].Penguin[ChoosePenguin].PositionY + Number;
                        Set[0][2] = Set[CounterSet][2];
                        Set[0][3] = Set[CounterSet][3];
                        Set[0][4] = Set[CounterSet][4];
                        CounterSet = 1;
                    }
                    else
                    {
                        if (compair_potential(Set[CounterSet - 1], Set[CounterSet]) == 0 && Set[CounterSet - 1][5] > Number)
                        {
                            Set[0][0] = Game->Player[Game->MyNumber].Penguin[ChoosePenguin].PositionX;
                            Set[0][1] = Game->Player[Game->MyNumber].Penguin[ChoosePenguin].PositionY + Number;
                            Set[0][2] = Set[CounterSet][2];
                            Set[0][3] = Set[CounterSet][3];
                            Set[0][4] = Set[CounterSet][4];
                            Set[0][5] = Number;
                            CounterSet = 1;
                        }
                    }
                }
            }
            Number++;
        }
        Number = 1;
        while (Game->Map[Game->Player[Game->MyNumber].Penguin[ChoosePenguin].PositionX][Game->Player[Game->MyNumber].Penguin[ChoosePenguin].PositionY - Number].Fish != 0 && Game->Map[Game->Player[Game->MyNumber].Penguin[ChoosePenguin].PositionX][Game->Player[Game->MyNumber].Penguin[ChoosePenguin].PositionY - Number].Player == -1)
        {
            if (count_direction(Game->Player[Game->MyNumber].Penguin[ChoosePenguin].PositionX, Game->Player[Game->MyNumber].Penguin[ChoosePenguin].PositionY - Number, Game) >= Prop && Game->Map[Game->Player[Game->MyNumber].Penguin[ChoosePenguin].PositionX][Game->Player[Game->MyNumber].Penguin[ChoosePenguin].PositionY - Number].Fish >= MinFish)
            {
                count_potential(Set[CounterSet], Game->Player[Game->MyNumber].Penguin[ChoosePenguin].PositionX, Game->Player[Game->MyNumber].Penguin[ChoosePenguin].PositionY - Number, Game);
                if (CounterSet == 0)
                {
                    Set[CounterSet][0] = Game->Player[Game->MyNumber].Penguin[ChoosePenguin].PositionX;
                    Set[CounterSet][1] = Game->Player[Game->MyNumber].Penguin[ChoosePenguin].PositionY - Number;
                    CounterSet++;
                }
                else
                {
                    if (compair_potential(Set[CounterSet - 1], Set[CounterSet]) > 0)
                    {
                        Set[0][0] = Game->Player[Game->MyNumber].Penguin[ChoosePenguin].PositionX;
                        Set[0][1] = Game->Player[Game->MyNumber].Penguin[ChoosePenguin].PositionY - Number;
                        Set[0][2] = Set[CounterSet][2];
                        Set[0][3] = Set[CounterSet][3];
                        Set[0][4] = Set[CounterSet][4];
                        CounterSet = 1;
                    }
                    else
                    {
                        if (compair_potential(Set[CounterSet - 1], Set[CounterSet]) == 0 && Set[CounterSet - 1][5] > Number)
                        {
                            Set[0][0] = Game->Player[Game->MyNumber].Penguin[ChoosePenguin].PositionX;
                            Set[0][1] = Game->Player[Game->MyNumber].Penguin[ChoosePenguin].PositionY - Number;
                            Set[0][2] = Set[CounterSet][2];
                            Set[0][3] = Set[CounterSet][3];
                            Set[0][4] = Set[CounterSet][4];
                            Set[0][5] = Number;
                            CounterSet = 1;
                        }
                    }
                }
            }
            Number++;
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
    Game->Player[Game->MyNumber].Score = Game->Player[Game->MyNumber].Score + Game->Map[x][y].Fish;
    Game->Map[x][y].Player = Game->MyNumber;
    Game->Map[Game->Player[Game->MyNumber].Penguin[ChoosePenguin].PositionX][Game->Player[Game->MyNumber].Penguin[ChoosePenguin].PositionY].Player = -1;
    Game->Map[Game->Player[Game->MyNumber].Penguin[ChoosePenguin].PositionX][Game->Player[Game->MyNumber].Penguin[ChoosePenguin].PositionY].Fish = 0;
    free(ListOfPenguins);
}