//#include "placement_phase.h"

void init_map(struct Game *TempGame)
{
    char Answer[20];
    do
    {
        while (generate_map(TempGame) <= TempGame->NumPlayers * TempGame->NumPenguins)
        {
        }
        print_map(TempGame);
        printf("Do you want to change the map(Y/N)\n");
        scanf("%s", Answer);
        while (!((Answer[0] == 'Y' && strlen(Answer) == 1) || (Answer[0] == 'N' && strlen(Answer) == 1)))
        {
            printf("Invalid answer.\nEnter correct answer:");
            scanf("%s", Answer);
        }
    } while (Answer[0] == 'Y' && strlen(Answer) == 1);
}
void init_player_data(struct Game *TempGame)
{
    int *OrderCheck, NameUnitCheck[300], *RandomOrder, RandomNumber, BotCounter = 0, RandomOrderBool;
    char Answer[20];
    OrderCheck = (int *)calloc(TempGame->NumPlayers, sizeof(int));
    RandomOrder = (int *)calloc(TempGame->NumPlayers, sizeof(int));
    for (int i = 0; i < TempGame->NumPlayers; i++)
    {
        RandomOrder[i] = i;
    }
    for (int i = 0; i < 300; i++)
    {
        NameUnitCheck[i] = 0;
    }
    NameUnitCheck['B'] = 1;
    printf("Choose turn order - randomly or manually (R/M):");
    scanf("%s", &Answer);
    while (strlen(Answer) != 1 || (Answer[0] != 'R' && Answer[0] != 'M'))
    {
        printf("Invalid answer.\nEnter correct answer:");
        scanf("%s", &Answer);
    }
    if (Answer[0] == 'R')
    {
        RandomOrderBool = 1;
    }
    else
    {
        RandomOrderBool = 0;
    }
    for (int i = 0; i < TempGame->NumPlayers; i++)
    {
        printf("Player number %d is Bot or Human(B/H):", i + 1);
        scanf("%s", &Answer);
        while (strlen(Answer) != 1 || (Answer[0] != 'H' && Answer[0] != 'B'))
        {
            printf("Invalid answer. Enter correct answer:");
            scanf("%s", &Answer);
        }
        if (Answer[0] == 'B')
        {
            printf("Choose the level of bot(1 to 8):");
            scanf("%d", &TempGame->Player[i].Bot);
            while (TempGame->Player[i].Bot < 1 || TempGame->Player[i].Bot > 8)
            {
                printf("Invalid answer. Enter correct answer(1 to 8):");
                scanf("%d", &TempGame->Player[i].Bot);
            }
            BotCounter += 1;
            TempGame->Player[i].NameUnit = 'B';
            TempGame->Player[i].Name[0] = 'B';
            TempGame->Player[i].Name[1] = 'o';
            TempGame->Player[i].Name[2] = 't';
            TempGame->Player[i].BotNumber = BotCounter;
            itoa(BotCounter, Answer, 10);
            for (int o = 0; o < strlen(Answer); o++)
            {
                TempGame->Player[i].Name[3 + o] = Answer[o];
            }
        }
        else
        {
            printf("Enter the nickname of Player:", i + 1);
            scanf("%s", &TempGame->Player[i].Name);
            while (check_names(i, TempGame) == 1)
            {
                printf("Invalid name.\nYour name can't be the same as another players'.\nEnter the name:");
                scanf("%s", &TempGame->Player[i].Name);
            }
            printf("Enter the name of the penguins (You can choose any one character except numbers exclude B):");
            scanf("%c", &TempGame->Player[i].NameUnit);
            scanf("%c", &TempGame->Player[i].NameUnit);
            while ((TempGame->Player[i].NameUnit >= '0' && TempGame->Player[i].NameUnit <= '9') || NameUnitCheck[TempGame->Player[i].NameUnit] == 1)
            {
                printf("Invalid character.\nYou can use any one character and the character can't be the same as another players and can't be B'.\nEnter the name of the penguins (You can choose any one character except numbers exclude B):");
                scanf("%c", &TempGame->Player[i].NameUnit);
                scanf("%c", &TempGame->Player[i].NameUnit);
            }
            NameUnitCheck[TempGame->Player[i].NameUnit] = 1;
        }
        if (RandomOrderBool == 1 || TempGame->Player[i].Bot == 1)
        {
            RandomNumber = rand() % (TempGame->NumPlayers - i);
            TempGame->Order[RandomOrder[RandomNumber]] = i;
            printf("Player %s (%c) moves %d.\n", TempGame->Player[i].Name, TempGame->Player[i].NameUnit, RandomOrder[RandomNumber] + 1);
            RandomOrder[RandomNumber] = RandomOrder[TempGame->NumPlayers - i - 1];
        }
        else
        {
            printf("Choose turn from 1 to %d:", TempGame->NumPlayers);
            scanf("%d", &RandomNumber);
            while (RandomNumber > TempGame->NumPlayers || RandomNumber <= 0 || OrderCheck[RandomNumber - 1] == 1)
            {
                printf("Invald turn.\nYou can use numbers from 1 to %d and turn can't be the same as another players'.\nChoose turn from 1 to %d:", TempGame->NumPlayers, TempGame->NumPlayers);
                scanf("%d", &RandomNumber);
            }
            TempGame->Order[RandomNumber - 1] = i;
            OrderCheck[RandomNumber - 1] = 1;
            RandomOrder[RandomNumber - 1] = RandomOrder[TempGame->NumPlayers - i - 1];
        }
    }
    free(OrderCheck);
    free(RandomOrder);
}

void init_coord_peng(struct Game *TempGame)
{
    int x, y;
    for (int i = 0; i < TempGame->NumPenguins; i++)
    {
        for (int o = 0; o < TempGame->NumPlayers; o++)
        {
            if (TempGame->Player[TempGame->Order[o]].Bot == 0)
            {
                print_map(TempGame);
                printf("Player %s (%c) choose the coordinates of your %d penguin:", TempGame->Player[TempGame->Order[o]].Name, TempGame->Player[TempGame->Order[o]].NameUnit, i + 1);
                scanf("%d%d", &x, &y);
                while ((x < 1 || x > TempGame->SizeMapX) || (y < 1 || y > TempGame->SizeMapY))
                {
                    printf("Invalid coordinates.\nUse coordinate X from 1 to %d and Y from 1 to %d:", TempGame->SizeMapX, TempGame->SizeMapY);
                    scanf("%d%d", &x, &y);
                }
                while (TempGame->Map[x][y].Fish != 1)
                {
                    printf("Invalid coordinates.\nThe coordinate should be free and with exactly 1 fish:");
                    scanf("%d%d", &x, &y);
                    while ((x < 1 || x > TempGame->SizeMapX) || (y < 1 || y > TempGame->SizeMapY))
                    {
                        printf(" Invalid coordinates.\nUse coordinate X from 1 to % d and Y from 1 to % d: ", TempGame->SizeMapX, TempGame->SizeMapY);
                        scanf("%d%d", &x, &y);
                    }
                }
                TempGame->Player[TempGame->Order[o]].Penguin[i].PositionX = x;
                TempGame->Player[TempGame->Order[o]].Penguin[i].PositionY = y;
                TempGame->Player[TempGame->Order[o]].Penguin[i].Movable = 0;
                TempGame->Map[x][y].Player = TempGame->Order[o];
                TempGame->Map[x][y].Penguin = i;
                TempGame->Player[TempGame->Order[o]].Score += TempGame->Map[x][y].Fish;
                TempGame->Map[x][y].Fish = 0;
            }
            else
            {
                bot_put_penguin(TempGame->Order[o], i, TempGame);
            }
        }
    }
    print_map(TempGame);
}