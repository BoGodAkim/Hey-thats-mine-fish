#ifndef BOT
#define BOT

int choose_penguins(int *ListOfPenguins, struct Game *Game);
int count_direction(int x, int y, struct Game *Game);
void count_potential(int *Potential, int X, int Y, struct Game *Game);
int compair_potential(int *Potential1, int *Potential2);
void find_all_cells_with_1(struct Game *Game, int (*CellWith1)[4], int *CountCell);
int bot_put_penguin(struct Game *Game);
void bot_make_turn(struct Game *Game);

#endif