// #include <stdio.h>
// #include <string.h>
// #include "struct.h"

int read_game(struct Game *Game, char *NameFile)
{
    FILE *frd;
    int NumberOfPenguins;
    char read[10];
    frd = fopen(NameFile, "r");
    if (frd == NULL)
    {
        return 1;
    }
    fscanf(frd, "%d%d", &Game->SizeMapX, &Game->SizeMapY);
    Game->Map = (struct Map **)calloc(Game->SizeMapX + 2, sizeof(struct Map *));
    for (int i = 0; i < Game->SizeMapX + 2; i++)
    {
        Game->Map[i] = (struct Map *)calloc(Game->SizeMapY + 2, sizeof(struct Map));
    }
    for (int x = 0; x < Game->SizeMapX + 2; x++)
    {
        for (int y = 0; y < Game->SizeMapY + 2; y++)
        {
            Game->Map[x][y].Player = -1;
        }
    }
    for (int x = 1; x < Game->SizeMapX + 1; x++)
    {
        for (int y = 1; y < Game->SizeMapY + 1; y++)
        {
            fscanf(frd, "%s", &read);
            if (strlen(read) != 2)
            {
                return 1;
            }
            Game->Map[x][y].Fish = read[0] - '0';
            Game->Map[x][y].Player = read[1] - '0';
            Game->Map[x][y].Player--;
            if (Game->Map[x][y].Player == 0)
            {
                NumberOfPenguins++;
            }
            if (Game->NumPlayers < Game->Map[x][y].Player + 1)
            {
                Game->NumPlayers = Game->Map[x][y].Player + 1;
            }
        }
    }
    Game->Player = (struct Player *)calloc(Game->NumPlayers, sizeof(struct Player));
    for (int i = 0; i < Game->NumPlayers; i++)
    {
        if (Game->NumPenguins != 0)
        {
            Game->Player[i].Penguin = (struct Penguin *)calloc(Game->NumPenguins, sizeof(struct Penguin));
        }
        else
        {
            Game->Player[i].Penguin = (struct Penguin *)calloc(NumberOfPenguins, sizeof(struct Penguin));
        }
    }
    for (int i = 0; i < Game->NumPlayers; i++)
    {
        fscanf(frd, "%s%*d%d", &Game->Player[i].Name, &Game->Player[i].Score);
    }
    fclose(frd);
    return 0;
}
void write_game(struct Game *Game, char *NameFile)
{
    FILE *fwr;
    fwr = fopen(NameFile, "w");
    fprintf(fwr, "%d %d\n", Game->SizeMapX, Game->SizeMapY);
    for (int x = 1; x < Game->SizeMapX + 1; x++)
    {
        for (int y = 1; y < Game->SizeMapY + 1; y++)
        {
            fprintf(fwr, "%d%d ", Game->Map[x][y].Fish, Game->Map[x][y].Player + 1);
        }
        fprintf(fwr, "\n");
    }
    for (int i = 0; i < Game->NumPlayers; i++)
    {
        fprintf(fwr, "%s %d %d\n", Game->Player[i].Name, i + 1, Game->Player[i].Score);
    }
    fclose(fwr);
}
void add_my_name(struct Game *Game, char *NameFile, char *MyName){
    FILE *fwr;
    fwr = fopen(NameFile, "r+");
    fseek(fwr, 0, SEEK_END);
    fprintf(fwr, "%s %d %d", MyName, Game->NumPlayers, 1);
}