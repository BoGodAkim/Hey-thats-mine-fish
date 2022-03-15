#ifndef CHECK
#define CHECK

int check_names(int PlayerNamber, struct Game *TempGame);
//int check_names(int PlayerNamber, struct Player *TempPlayerData);
// Returns 1 if the name of a player of the given number
// already exists in the list of players, 0 otherwise
// PlayerNumber - number of a player whose name is to be checked in the list
// PlayerData - array of Player structures
// 		 (a list of players with their attributes)

int check_penguin(int CoordPengX, int CoordPengY, struct Game *TempGame);
//int check_penguin(int TempSizeMapX, int TempSizeMapY, int CoordPengX, int CoordPengY, struct Map (*TempBoard)[TempSizeMapY]);
// Returns 1 if a penguin can move, 0 otherwise
// SizeMapX, SizeMapY - width and height of the board
// CoordPengX, CoordPengY - position of the penguin
// Board - board array

void check_all_penguins(struct Game *TempGame);
//void check_all_penguins(int TempSizeMapX, int TempSizeMapY, int TempNumPlayer, int TempNumPeng, struct Penguin (*TempPenguinData)[TempNumPeng], struct Map (*TempBoard)[TempSizeMapY]);
// Updates every element of penguin data array with appropriate value of member "Movable"
// SizeMapX, SizeMapY - width and height of the map
// NumPlayer - total number of players
// NumPeng - number of penguins for each player
// PenguinData - array in which data of all penguins is stored
// Board - board array

int check_status(struct Game *TempGame);
//int check_status(int TempNumPlayer, struct Player *TempPlayerData);
// Checks if all players can move (but any or all of their penguins?)
// Returns 1 if so, 0 otherwise
// NumPlayer - total number of players
// PlayerData - array in which data of all players is stored

int check_turn(int CoordPengX, int CoordPengY, int CoordTurnX, int CoordTurnY, struct Game *TempGame);
//int check_turn(int TempSizeMapX, int TempSizeMapY, int CoordPengX, int CoordPengY, int CoordTurnX, int CoordTurnY, struct Map (*TempBoard)[TempSizeMapY]);
// Checks if penguin can move from some coordinates to some coordinates
// Returns 1 if a move is vertical or horizontal and there is at least one floe with at least one fish on it
// Returns 0 if a move is diagonal or there are no fishes on the way
// SizeMapX, SizeMapY - width and height of the map
// CoordPengX, CoordPengY - actual coordinates of a penguin
// CoordTurnX, CoordTurnY - where we want to move the penguin
// Board - board array

void check_all_players(struct Game *TempGame);
//void check_all_players(int TempNumPlayer, int TempNumPeng, struct Player *TempPlayerData, struct Penguin (*TempPenguinData)[TempNumPeng]);
// For each player in PlayerData array
// sets his mobility member "Movable" to true if all of his penguins can move
// NumPlayer - total number of players
// NumPeng - number of penguins for each player
// PlayerData - array in which data of all players is stored
// PenguinData - array in which data of all penguins is stored 

#endif