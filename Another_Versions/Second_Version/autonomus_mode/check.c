int check_penguin(int CoordPengX, int CoordPengY, struct Game *Game)
{
    if ((Game->Map[CoordPengX + 1][CoordPengY].Fish == 0 || Game->Map[CoordPengX + 1][CoordPengY].Player != -1) && (Game->Map[CoordPengX][CoordPengY + 1].Fish == 0 || Game->Map[CoordPengX][CoordPengY + 1].Player != -1) && (Game->Map[CoordPengX - 1][CoordPengY].Fish == 0 || Game->Map[CoordPengX - 1][CoordPengY].Player != -1) && (Game->Map[CoordPengX][CoordPengY - 1].Fish == 0 || Game->Map[CoordPengX][CoordPengY - 1].Player != -1))
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
        for (int u = 0; u < Game->Player[i].NumberOfPenguins; u++)
        {
            Game->Player[i].Penguin[u].Movable = check_penguin(Game->Player[i].Penguin[u].PositionX, Game->Player[i].Penguin[u].PositionY, Game);
        }
    }
}
void check_all_players(struct Game *Game)
{
    int x = 0;
    for (int i = 0; i < Game->NumPlayers; i++)
    {
        x = 0;
        for (int u = 0; u < Game->Player[i].NumberOfPenguins; u++)
        {
            x = x + Game->Player[i].Penguin[u].Movable;
        }
        if (x == Game->Player[i].NumberOfPenguins)
        {
            Game->Player[i].Movable = 1;
        }
    }
}
void fill_data_about_penguins(struct Game *Game)
{
    for (int x = 1; x < Game->SizeMapX + 1; x++)
    {
        for (int y = 1; y < Game->SizeMapY + 1; y++)
        {
            if (Game->Map[x][y].Player != -1)
            {
                Game->Player[Game->Map[x][y].Player].Penguin[Game->Player[Game->Map[x][y].Player].NumberOfPenguins].PositionX = x;
                Game->Player[Game->Map[x][y].Player].Penguin[Game->Player[Game->Map[x][y].Player].NumberOfPenguins].PositionY = y;
                Game->Player[Game->Map[x][y].Player].NumberOfPenguins++;
            }
        }
    }
}
int find_my_number(struct Game *Game, char *Name)
{
    Game->MyNumber = -1;
    for (int i = 0; i < Game->NumPlayers; i++)
    {
        if (strcmp(Game->Player[i].Name, Name) == 0)
        {
            if (Game->MyNumber != -1)
            {
                return 1;
            }
            Game->MyNumber = i;
        }
    }
    return 0;
}
