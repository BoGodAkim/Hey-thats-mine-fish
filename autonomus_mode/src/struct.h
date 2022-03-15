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
    char *Name;
    struct Penguin *Penguin;
};
// // represents a single player: can be a bot or a human
// //  int Score - score of the player
// //  int Movable - flag for signaling if player can make moves
// //  int Bot - flag for indicating if player is a bot and at the same time
// //  char NameUnit - name of player`s penguins displayed on the board
// //  char Name[200] - player name

struct Map
{
    int8_t Fish;
    int Player;
};
// // represents a cell on the map on which can contain penguin or be empty
// //  int8_t Fish - number of fish on this cell
// //  int Player - player number on this cell
// //  int Penguin - penguin number on this cell

struct Penguin
{
    int PositionX;
    int PositionY;
    int Movable;
};
// // represents a penguin on the board
// //  int PositionX, int PositionY - coordinates of the penguin
// //  int Movable - flag for marking penguin as movable or not
