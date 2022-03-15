#include <stdint.h>
struct Game
{
    int NumPlayers;
    int NumPenguins;
    int SizeMapX;
    int SizeMapY;
    int *Order;
    struct Map **Map;
    struct Player *Player;
};
// int NumPlayers - number of players in game
// int NumPenguins - number of penguins in game 
// int SizeMapX , int SizeMapY - size of map
// int *Order - this array save in witch order players make turns
// struct Map **Map - this struct save data about map
// struct Player *Player - this struct save data about players

struct Player
{
    int Score;
    int Movable;
    int Bot;
    int BotNumber;
    char NameUnit;
    char Name[200];
    struct Penguin *Penguin;
};
// represents a single player: can be a bot or a human
//  int Score - score of the player
//  int Movable - flag for signaling if player can make moves
//  int Bot - flag for indicating if player is a bot and at the same time
//  int BotNumber - number of bot in game
//  char NameUnit - name of player`s penguins displayed on the board
//  char Name[200] - player name

struct Map
{
    int8_t Fish;
    int Player;
    int Penguin;
};
// represents a cell on the map on which can contain penguin or be empty
//  int8_t Fish - number of fish on this cell
//  int Player - player number on this cell
//  int Penguin - penguin number on this cell

struct Penguin
{
    int PositionX;
    int PositionY;
    int Movable;
};
// represents a penguin on the board
//  int PositionX, int PositionY - coordinates of the penguin
//  int Movable - flag for marking penguin as movable or not
