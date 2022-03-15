#ifndef MOVE
#define MOVE

void init_coord_peng(struct Game *Game);
// Take data about Game(struct Game *Game)
// This function put penguins on the board automatically or manually and save it in board data(Board)

void player_turn(int PlayerNumber, struct Game *Game);
// Take data about Game(struct Game *Game) and number of Player which move(PlayerNumber)
// This functian take move from and to coordinates which enter player

#endif