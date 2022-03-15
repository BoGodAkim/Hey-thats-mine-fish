//#include "movement_phase.h"

void player_turn(int PlayerNumber, struct Game *TempGame)
{
    int xp, yp;
    int x, y;
    if (TempGame->NumPenguins > 1)
    {
        printf("Player %s (%c) enter the number of your penguin to choose him(1 to %d):", TempGame->Player[PlayerNumber].Name, TempGame->Player[PlayerNumber].NameUnit, TempGame->NumPenguins);
        scanf("%d", &x);
        while (x < 1 || x > TempGame->NumPenguins || TempGame->Player[PlayerNumber].Penguin[x - 1].Movable == 1)
        {
            printf("Invalid number.\nUse number from 1 to %d:", TempGame->NumPenguins);
            scanf("%d", &x);
        }
        xp = TempGame->Player[PlayerNumber].Penguin[x - 1].PositionX;
        yp = TempGame->Player[PlayerNumber].Penguin[x - 1].PositionY;
    }
    else
    {
        xp = TempGame->Player[PlayerNumber].Penguin[0].PositionX;
        yp = TempGame->Player[PlayerNumber].Penguin[0].PositionY;
    }
    printf("Player %s (%c) choose coordinates in which your penguin go:", TempGame->Player[PlayerNumber].Name, TempGame->Player[PlayerNumber].NameUnit, TempGame->NumPenguins);
    scanf("%d%d", &x, &y);
    while ((x < 1 || x > TempGame->SizeMapX) || (y < 1 || y > TempGame->SizeMapY))
    {
        printf("Invalid coordinates.\nUse coordinate X from 1 to %d and Y from 1 to %d:", TempGame->SizeMapX, TempGame->SizeMapY);
        scanf("%d%d", &x, &y);
    }
    while (check_turn(xp, yp, x, y, TempGame) == 1)
    {
        printf("Invalid coordinates.\nYou need to choose coordinates in which your penguin can go:");
        scanf("%d%d", &x, &y);
        while ((x < 1 || x > TempGame->SizeMapX) || (y < 1 || y > TempGame->SizeMapY))
        {
            printf(" Invalid coordinates.\nUse coordinate X from 1 to % d and Y from 1 to % d: ", TempGame->SizeMapX, TempGame->SizeMapY);
            scanf("%d%d", &x, &y);
        }
    }
    TempGame->Player[PlayerNumber].Score = TempGame->Player[PlayerNumber].Score + TempGame->Map[x][y].Fish;
    TempGame->Map[x][y].Fish = 0;
    TempGame->Map[x][y].Player = TempGame->Map[xp][yp].Player;
    TempGame->Map[x][y].Penguin = TempGame->Map[xp][yp].Penguin;
    TempGame->Map[xp][yp].Player = -1;
    TempGame->Map[xp][yp].Penguin = -1;
    TempGame->Player[PlayerNumber].Penguin[TempGame->Map[x][y].Penguin].PositionX = x;
    TempGame->Player[PlayerNumber].Penguin[TempGame->Map[x][y].Penguin].PositionY = y;
    TempGame->Player[PlayerNumber].Penguin[TempGame->Map[x][y].Penguin].Movable = check_penguin(TempGame->Player[PlayerNumber].Penguin[TempGame->Map[x][y].Penguin].PositionX, TempGame->Player[PlayerNumber].Penguin[TempGame->Map[x][y].Penguin].PositionY, TempGame);
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
    print_map(TempGame);
}