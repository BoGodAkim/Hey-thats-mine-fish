#ifndef CHECK
#define CHECK

int check_penguin(int CoordPengX, int CoordPengY, struct Game *Game);
void check_all_penguins(struct Game *Game);
void check_all_players(struct Game *Game);
void fill_data_about_penguins(struct Game *Game);
int find_my_number(struct Game *Game, char *Name);

#endif