typedef struct Penguin
{
    int pos_X;
    int pos_Y;
    int canMove;
} Penguin;
// represents a penguin on the board
//  int pos_X, int pos_Y - coordinates of the penguin
//  int canMove - flag for marking penguin as movable or not

typedef struct Player
{
    char name[100];
    int score;
    int haveMoves;
    Penguin *Penguin;
} Player;
// represents a single player: can be a bot or a human
//  int score - score of the player
//  int haveMoves - flag for signaling if player can make moves
//  char name[100] - player name

typedef struct Board
{
    int Fish;
    int Player;
    int Penguin;
} Board;
// represents a cell on the map on which can contain penguin or be empty
//  int Fish - number of fish on this cell
//  int Player - player number on this cell
//  int Penguin - penguin number on this cell

typedef struct GameData{
    int boardWidth;
    int boardHeight;
    int penguinsCount;
    int playersCount;
    Player *Player;
    Board **Board;
}GameData;
// int playersCount - number of players in game
// int penguinsCount - number of penguins in game
// int boardWidth , int boardHeight - size of map
// Board **Board - this struct save data about map
// Player *Player - this struct save data about players