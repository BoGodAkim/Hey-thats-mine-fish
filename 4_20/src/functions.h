#ifndef CHECK
#define CHECK

void initData(GameData *Game);

int check_names(int curPlayer, GameData *Game);
// Take data about Game(GameData *Game) and number of a player whose name is to be checked in the list(int curPlayer)
// Returns 1 if the name of a player of the given number
// already exists in the list of players, 0 otherwise

int check_penguin(int CoordX, int CoordY, GameData *Game);
// Take data about Game(GameData *Game) and position of the penguin(int CoordX, int CoordY)
// Returns 1 if a penguin can move, 0 otherwise

void check_all_penguins(GameData *Game);
// Take data about Game(GameData *Game)
// Updates every element of penguin data array with appropriate value of member "Movable"

void check_all_players(GameData *Game);
// Take data about Game(GameData *Game)
// For each player in PlayerData array
// sets his mobility member "Movable" to true if all of his penguins can move

int check_status(GameData *Game);
// Take data about Game(GameData *Game)
// Checks if all players can move (but any or all of their penguins?)
// Returns 1 if so, 0 otherwise

int check_turn(int CoordPengX, int CoordPengY, int CoordTurnX, int CoordTurnY, GameData *Game);
// Take data about Game(GameData *Game), position of the penguin(int CoordPengX, int CoordPengY) and where we want to move the penguin(int CoordTurnX, int CoordTurnY)
// Checks if penguin can move from some coordinates to some coordinates
// Returns 1 if a move is vertical or horizontal and there is at least one floe with at least one fish on it
// Returns 0 if a move is diagonal or there are no fishes on the way

void print_map(GameData *Game);
// Take data about Game(GameData *Game)
// Prints map to the console

void sort_score(int playersCount, int *score, int *playerScore);
// Take data about Game(GameData *Game)
// Sort score for displaying in the console

void print_scoreboard(int *score, int *playerScore, GameData *Game);
// Take data about Game(GameData *Game)
// Displays scoreboard to the console

#endif