#ifndef CHECK
#define CHECK

int check_names(int PlayerNamber, struct Game *TempGame);
// Take data about Game(struct Game *TempGame) and number of a player whose name is to be checked in the list(int PlayerNamber)
// Returns 1 if the name of a player of the given number
// already exists in the list of players, 0 otherwise

int check_penguin(int CoordPengX, int CoordPengY, struct Game *TempGame);
// Take data about Game(struct Game *TempGame) and position of the penguin(int CoordPengX, int CoordPengY)
// Returns 1 if a penguin can move, 0 otherwise

void check_all_penguins(struct Game *TempGame);
// Take data about Game(struct Game *TempGame)
// Updates every element of penguin data array with appropriate value of member "Movable"


int check_status(struct Game *TempGame);
// Take data about Game(struct Game *TempGame)
// Checks if all players can move (but any or all of their penguins?)
// Returns 1 if so, 0 otherwise

int check_turn(int CoordPengX, int CoordPengY, int CoordTurnX, int CoordTurnY, struct Game *TempGame);
// Take data about Game(struct Game *TempGame), position of the penguin(int CoordPengX, int CoordPengY) and where we want to move the penguin(int CoordTurnX, int CoordTurnY)
// Checks if penguin can move from some coordinates to some coordinates
// Returns 1 if a move is vertical or horizontal and there is at least one floe with at least one fish on it
// Returns 0 if a move is diagonal or there are no fishes on the way

void check_all_players(struct Game *TempGame);
// Take data about Game(struct Game *TempGame)
// For each player in PlayerData array
// sets his mobility member "Movable" to true if all of his penguins can move

#endif