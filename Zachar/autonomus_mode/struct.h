#include <stdint.h>
struct Game
{
    int Phase;
    int MyNumber;
    int NumPlayers;
    int NumPenguins;
    int SizeMapX;
    int SizeMapY;
    struct Map **Map;
    struct Player *Player;
};

struct Player
{
    int Score;
    int Movable;
    int NumberOfPenguins;
    char Name[256];
    struct Penguin *Penguin;
};

struct Map
{
    int8_t Fish;
    int Player;
};


struct Penguin
{
    int PositionX;
    int PositionY;
    int Movable;
};

