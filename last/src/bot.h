#ifndef BOT
#define BOT

int choose_penguins(int IDPlayer, int *ListOfPenguins, struct Game *TempGame);
// Take data about Game(struct Game *TempGame)
// Take information about number of player witch make turn(IDPlayer)
// Take array which save number of penguins which need to move(ListOfPenguins)
// This function find which penguins of player(IDplayer) need to move and save their number in ListOfPenguin
// Return count of penguins which need to move

int count_direction(int x, int y, struct Game *TempGame);
// Take coordinates(x, y) and take data about Game(struct Game *TempGame)
// This function check in which direction penguin can move from coordinate(x, y) and return count of them

void count_potential(int *Potential, int X, int Y, struct Game *TempGame);
// Take array in which save potential of coordinates(Potential), coordinates of cell for which cout potential(X,Y)
// Take data about Game(struct Game *TempGame)
// This function count potential of cell(X, Y) and save it(Potential)

int compair_potential(int *Potential1, int *Potential2);
// Take array if Potential1 and Potentail2
// Comapre which potential is bigger
// Return: 1(Potential1 < Potential2), -1(Potential1 > Potential2), 0(Potential1 == Potential2)

int compair_potential_Vers_II(int *Potential1, int *Potential2);
//  Take array if Potential1 and Potentail2
//  Comapre which potential is bigger
//  Return: 1(Potential1 < Potential2), -1(Potential1 > Potential2), 0(Potential1 == Potential2)

int find_all_cells_with_1(struct Game *TempGame, int **TempCellWith1);
// Take data about Game(struct Game *TempGame) and array of coordinates cells with 1 fish(TempCellWith1)
//  This function find all cells with 1 fish, save their coordinates in TempCellWith1
//  Return count of cells with 1 fish

void random_put_penguin(int IDPlayer, int IDPenguin, struct Game *TempGame);
// Take number of player which put penguin(IDPlayer), number of penguin which put(IDPenguin) and take data about Game(struct Game *TempGame)
// This function put penguin on the map

void put_penguin_with_potential(int IDPlayer, int IDPenguin, struct Game *TempGame);
// Take number of player which put penguin(IDPlayer), number of penguin which put(IDPenguin) and take data about Game(struct Game *TempGame)
// This function put penguin on the map

void put_penguin_with_potential_Vers_II(int IDPlayer, int IDPenguin, struct Game *TempGame);
// Take number of player which put penguin(IDPlayer), number of penguin which put(IDPenguin) and take data about Game(struct Game *TempGame)
// This function put penguin on the map

void bot_level_1(int IDPlayer, struct Game *TempGame);
// Take number of player which move(IDPlayer) and take data about Game(struct Game *TempGame)
// Take data about players(TempPlayerData), penguins(TempPenguinsData) and board(TempBoard)
// This function make turn

void bot_level_2(int IDPlayer, struct Game *TempGame);
// Take number of player which move(IDPlayer) and take data about Game(struct Game *TempGame)
// Take data about players(TempPlayerData), penguins(TempPenguinsData) and board(TempBoard)
// This function make turn

void bot_level_3(int IDPlayer, struct Game *TempGame);
// Take number of player which move(IDPlayer) and take data about Game(struct Game *TempGame)
// Take data about players(TempPlayerData), penguins(TempPenguinsData) and board(TempBoard)
// This function make turn

void bot_level_4(int IDPlayer, struct Game *TempGame);
// Take number of player which move(IDPlayer) and take data about Game(struct Game *TempGame)
// Take data about players(TempPlayerData), penguins(TempPenguinsData) and board(TempBoard)
// This function make turn

void bot_level_5(int IDPlayer, struct Game *TempGame);
// Take number of player which move(IDPlayer) and take data about Game(struct Game *TempGame)
// Take data about players(TempPlayerData), penguins(TempPenguinsData) and board(TempBoard)
// This function make turn

void bot_level_6(int IDPlayer, struct Game *TempGame);
// Take number of player which move(IDPlayer) and take data about Game(struct Game *TempGame)
// Take data about players(TempPlayerData), penguins(TempPenguinsData) and board(TempBoard)
// This function make turn

void bot_level_7(int IDPlayer, struct Game *TempGame);
// Take number of player which move(IDPlayer) and take data about Game(struct Game *TempGame)
// Take data about players(TempPlayerData), penguins(TempPenguinsData) and board(TempBoard)
// This function make turn

void bot_level_8(int IDPlayer, struct Game *TempGame);
// Take number of player which move(IDPlayer) and take data about Game(struct Game *TempGame)
// Take data about players(TempPlayerData), penguins(TempPenguinsData) and board(TempBoard)
// This function make turn

void bot_put_penguin(int IDPlayer, int IDPenguin, struct Game *TempGame);
// Take number of player which put penguin(IDPlayer), number of penguin which put(IDPenguin) and take data about Game(struct Game *TempGame)
// This function read from player data(TempPlayerData) level of bot and call function for this level which put penguin

void bot_turn(int IDPlayer, struct Game *TempGame);
// void bot_turn(int IDPlayer, int TempSizeMapX, int TempSizeMapY, int TempNumPlayer, int TempNumPeng, struct Player *TempPlayerData, struct Penguin (*TempPenguinData)[TempNumPeng], struct Map (*TempBoard)[TempSizeMapY + 2]);
//  Take number of player which move(IDPlayer), size of board(TempSizeMapX, TempSizeMapY), number of players and penguins for each player(TempNumPlayer, TempNumPeng)
//  Take data about players(TempPlayerData), penguins(TempPenguinsData) and board(TempBoard)
//  This function read from player data(TempPlayerData) level of bot and call function fro this level which make turn

#endif