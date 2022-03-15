//#include "movement_phase.h"

void init_coord_peng(struct Game *Game)
{
    int x, y;
    for (int i = 0; i < Game->NumPenguins; i++)
    {
        for (int o = 0; o < Game->NumPlayers; o++)
        {
            print_map(Game);
            printf("Player %s (%c) choose the coordinates of your %d penguin:", Game->Player[Game->Order[o]].Name, Game->Player[Game->Order[o]].NameUnit, i + 1);
            scanf("%d%d", &x, &y);
            while ((x < 1 || x > Game->SizeMapX) || (y < 1 || y > Game->SizeMapY))
            {
                printf("Invalid coordinates.\nUse coordinate X from 1 to %d and Y from 1 to %d:", Game->SizeMapX, Game->SizeMapY);
                scanf("%d%d", &x, &y);
            }
            while (Game->Map[x][y].Fish != 1)
            {
                printf("Invalid coordinates.\nThe coordinate should be free and with exactly 1 fish:");
                scanf("%d%d", &x, &y);
                while ((x < 1 || x > Game->SizeMapX) || (y < 1 || y > Game->SizeMapY))
                {
                    printf(" Invalid coordinates.\nUse coordinate X from 1 to % d and Y from 1 to % d: ", Game->SizeMapX, Game->SizeMapY);
                    scanf("%d%d", &x, &y);
                }
            }
            Game->Player[Game->Order[o]].Penguin[i].PositionX = x;
            Game->Player[Game->Order[o]].Penguin[i].PositionY = y;
            Game->Player[Game->Order[o]].Penguin[i].Movable = 0;
            Game->Map[x][y].Player = Game->Order[o];
            Game->Map[x][y].Penguin = i;
            Game->Player[Game->Order[o]].Score += Game->Map[x][y].Fish;
            Game->Map[x][y].Fish = 0;
        }
    }
    print_map(Game);
}

void player_turn(int PlayerNumber, struct Game *Game)
{
    int xp, yp;
    int x, y;
    if (Game->NumPenguins > 1)
    {
        printf("Player %s (%c) enter the number of your penguin to choose him(1 to %d):", Game->Player[PlayerNumber].Name, Game->Player[PlayerNumber].NameUnit, Game->NumPenguins);
        scanf("%d", &x);
        while (x < 1 || x > Game->NumPenguins || Game->Player[PlayerNumber].Penguin[x - 1].Movable == 1)
        {
            printf("Invalid number.\nUse number from 1 to %d:", Game->NumPenguins);
            scanf("%d", &x);
        }
        xp = Game->Player[PlayerNumber].Penguin[x - 1].PositionX;
        yp = Game->Player[PlayerNumber].Penguin[x - 1].PositionY;
    }
    else
    {
        xp = Game->Player[PlayerNumber].Penguin[0].PositionX;
        yp = Game->Player[PlayerNumber].Penguin[0].PositionY;
    }
    printf("Player %s (%c) choose coordinates in which your penguin go:", Game->Player[PlayerNumber].Name, Game->Player[PlayerNumber].NameUnit, Game->NumPenguins);
    scanf("%d%d", &x, &y);
    while ((x < 1 || x > Game->SizeMapX) || (y < 1 || y > Game->SizeMapY))
    {
        printf("Invalid coordinates.\nUse coordinate X from 1 to %d and Y from 1 to %d:", Game->SizeMapX, Game->SizeMapY);
        scanf("%d%d", &x, &y);
    }
    while (check_turn(xp, yp, x, y, Game) == 1)
    {
        printf("Invalid coordinates.\nYou need to choose coordinates in which your penguin can go:");
        scanf("%d%d", &x, &y);
        while ((x < 1 || x > Game->SizeMapX) || (y < 1 || y > Game->SizeMapY))
        {
            printf(" Invalid coordinates.\nUse coordinate X from 1 to % d and Y from 1 to % d: ", Game->SizeMapX, Game->SizeMapY);
            scanf("%d%d", &x, &y);
        }
    }
    Game->Player[PlayerNumber].Score = Game->Player[PlayerNumber].Score + Game->Map[x][y].Fish;
    Game->Map[x][y].Fish = 0;
    Game->Map[x][y].Player = Game->Map[xp][yp].Player;
    Game->Map[x][y].Penguin = Game->Map[xp][yp].Penguin;
    Game->Map[xp][yp].Player = -1;
    Game->Map[xp][yp].Penguin = -1;
    Game->Player[PlayerNumber].Penguin[Game->Map[x][y].Penguin].PositionX = x;
    Game->Player[PlayerNumber].Penguin[Game->Map[x][y].Penguin].PositionY = y;
    Game->Player[PlayerNumber].Penguin[Game->Map[x][y].Penguin].Movable = check_penguin(Game->Player[PlayerNumber].Penguin[Game->Map[x][y].Penguin].PositionX, Game->Player[PlayerNumber].Penguin[Game->Map[x][y].Penguin].PositionY, Game);
    if (Game->Map[x + 1][y].Player != -1)
    {
        Game->Player[Game->Map[x + 1][y].Player].Penguin[Game->Map[x + 1][y].Penguin].Movable = check_penguin(x + 1, y, Game);
    }
    if (Game->Map[x - 1][y].Player != -1)
    {
        Game->Player[Game->Map[x - 1][y].Player].Penguin[Game->Map[x - 1][y].Penguin].Movable = check_penguin(x - 1, y, Game);
    }
    if (Game->Map[x][y + 1].Player != -1)
    {
        Game->Player[Game->Map[x][y + 1].Player].Penguin[Game->Map[x][y + 1].Penguin].Movable = check_penguin(x, y + 1, Game);
    }
    if (Game->Map[x][y - 1].Player != -1)
    {
        Game->Player[Game->Map[x][y - 1].Player].Penguin[Game->Map[x][y - 1].Penguin].Movable = check_penguin(x, y - 1, Game);
    }
    print_map(Game);
}