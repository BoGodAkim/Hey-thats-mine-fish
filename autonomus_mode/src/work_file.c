// #include <stdio.h>
// #include <string.h>
// #include "struct.h"

int read_game_cache(struct Game *TempGame, char *NameFile)
{
    FILE *frd;
    frd = fopen(NameFile, "r");
    if (frd == NULL)
    {
        return 1;
    }
    fscanf(frd, "%d%d%d%d%d%d", &TempGame->SizeMapX, &TempGame->SizeMapY, &TempGame->NumPlayers, &TempGame->NumPenguins, &TempGame->Phase, &TempGame->MyNumber);
    TempGame->Map = (struct Map **)calloc(TempGame->SizeMapX + 2, sizeof(struct Map *));
    for (int i = 0; i < TempGame->SizeMapX + 2; i++)
    {
        TempGame->Map[i] = (struct Map *)calloc(TempGame->SizeMapY + 2, sizeof(struct Map));
    }
    TempGame->Player = (struct Player *)calloc(TempGame->NumPlayers, sizeof(struct Player));
    for (int i = 0; i < TempGame->NumPlayers; i++)
    {
        TempGame->Player[i].Penguin = (struct Penguin *)calloc(TempGame->NumPenguins, sizeof(struct Penguin));
    }
    for (int x = 1; x < TempGame->SizeMapX + 1; x++)
    {
        for (int y = 1; y < TempGame->SizeMapY + 1; y++)
        {
            fscanf(frd, "%d%d", &TempGame->Map[x][y].Fish, &TempGame->Map[x][y].Player);
        }
    }
    char str[200];
    for (int i = 0; i < TempGame->NumPlayers; i++)
    {
        fscanf(frd, "%s%d%d%d", &str, &TempGame->Player[i].Movable, &TempGame->Player[i].NumberOfPenguins, &TempGame->Player[i].Score);
        TempGame->Player[TempGame->NumPlayers].Name = (char *)calloc(strlen(str) + 1, sizeof(char));
        for (int u = 0; u < strlen(str);u++){
            TempGame->Player[i].Name[u] = str[u];
        }
        TempGame->Player[i].Name[strlen(str)] = 0;
    }
    fclose(frd);
    return 0;
}
void write_game_cache(struct Game *TempGame, char *NameFile)
{
    FILE *fwr;
    fwr = fopen(NameFile, "w");
    fprintf(fwr, "%d %d %d %d %d %d \n", TempGame->SizeMapX, TempGame->SizeMapY, TempGame->NumPlayers, TempGame->NumPenguins, TempGame->Phase, TempGame->MyNumber);
    fprintf(fwr, "\n");
    for (int x = 1; x < TempGame->SizeMapX + 1; x++)
    {
        for (int y = 1; y < TempGame->SizeMapY + 1; y++)
        {
            fprintf(fwr, "%d %d ", TempGame->Map[x][y].Fish, TempGame->Map[x][y].Player);
        }
        fprintf(fwr, "\n");
    }
    for (int i = 0; i < TempGame->NumPlayers; i++)
    {
        fprintf(fwr, "%s %d %d %d \n", TempGame->Player[i].Name, TempGame->Player[i].Movable, TempGame->Player[i].NumberOfPenguins, TempGame->Player[i].Score);
    }
    fclose(fwr);
}
int read_game(struct Game *TempGame, char *NameFile)
{
    FILE *frd;
    int NumberOfPenguins;
    char read[10];
    frd = fopen(NameFile, "r");
    if (frd == NULL)
    {
        return 1;
    }
    fscanf(frd, "%d%d", &TempGame->SizeMapX, &TempGame->SizeMapY);
    TempGame->Map = (struct Map **)calloc(TempGame->SizeMapX + 2, sizeof(struct Map *));
    for (int i = 0; i < TempGame->SizeMapX + 2; i++)
    {
        TempGame->Map[i] = (struct Map *)calloc(TempGame->SizeMapY + 2, sizeof(struct Map));
    }
    for (int x = 0; x < TempGame->SizeMapX + 2; x++)
    {
        for (int y = 0; y < TempGame->SizeMapY + 2; y++)
        {
            TempGame->Map[x][y].Player = -1;
        }
    }
    for (int x = 1; x < TempGame->SizeMapX + 1; x++)
    {
        for (int y = 1; y < TempGame->SizeMapY + 1; y++)
        {
            fscanf(frd, "%s", &read);
            if (strlen(read) != 2)
            {
                return 1;
            }
            TempGame->Map[x][y].Fish = read[0] - '0';
            TempGame->Map[x][y].Player = read[1] - '0';
            TempGame->Map[x][y].Player--;
            if (TempGame->Map[x][y].Player == 0)
            {
                NumberOfPenguins++;
            }
            if (TempGame->NumPlayers < TempGame->Map[x][y].Player + 1)
            {
                TempGame->NumPlayers = TempGame->Map[x][y].Player + 1;
            }
        }
    }
    TempGame->Player = (struct Player *)calloc(TempGame->NumPlayers, sizeof(struct Player));
    for (int i = 0; i < TempGame->NumPlayers; i++)
    {
        if (TempGame->NumPenguins != 0)
        {
            TempGame->Player[i].Penguin = (struct Penguin *)calloc(TempGame->NumPenguins, sizeof(struct Penguin));
        }
        else
        {
            TempGame->Player[i].Penguin = (struct Penguin *)calloc(NumberOfPenguins, sizeof(struct Penguin));
        }
    }
    char str[200];
    for (int i = 0; i < TempGame->NumPlayers; i++)
    {
        fscanf(frd, "%s%*d%d", &str, &TempGame->Player[i].Score);
        TempGame->Player[TempGame->NumPlayers].Name = (char *)calloc(strlen(str) + 1, sizeof(char));
        for (int u = 0; u < strlen(str); u++)
        {
            TempGame->Player[i].Name[u] = str[u];
        }
        TempGame->Player[i].Name[strlen(str)] = 0;
    }
    fclose(frd);
    return 0;
}
void write_game(struct Game *TempGame, char *NameFile)
{
    FILE *fwr;
    fwr = fopen(NameFile, "w");
    fprintf(fwr, "%d %d\n", TempGame->SizeMapX, TempGame->SizeMapY);
    for (int x = 1; x < TempGame->SizeMapX + 1; x++)
    {
        for (int y = 1; y < TempGame->SizeMapY + 1; y++)
        {
            fprintf(fwr, "%d%d ", TempGame->Map[x][y].Fish, TempGame->Map[x][y].Player + 1);
        }
        fprintf(fwr, "\n");
    }
    for (int i = 0; i < TempGame->NumPlayers; i++)
    {
        fprintf(fwr, "%s %d %d\n", TempGame->Player[i].Name, i + 1, TempGame->Player[i].Score);
    }
    fclose(fwr);
}