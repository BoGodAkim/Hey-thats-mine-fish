#ifndef PLACE
#define PLACE

void init_map(struct Game *TempGame);
// Take data about Game(struct Game *TempGame)
// This function generat board using fuction (creat_map) and print it using function (print_map) until is satisfied a result
// Function save the final map in TempBoard and nothing return

void init_player_data(struct Game *TempGame);
// Take data about Game(struct Game *TempGame)
// This function take from each Player data about them or bot and save it in TempPlayerData
// This function returns nothing

void init_coord_peng(struct Game *TempGame);
// Take data about Game(struct Game *TempGame)
// This function put penguins on the board automatically or manually and save it in board data(TempBoard)

#endif