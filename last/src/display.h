#ifndef DISP
#define DISP

void print_map(struct Game *TempGame);
// Take data about Game(struct Game *TempGame)
// Prints map to the console


void sort_score(int TempNumPlayer, int *TempScore, int *TempPlayerScore);
// Take data about Game(struct Game *TempGame)
// Sort score for displaying in the console

void print_scoreboard(int *TempScore, int *TempPlayerScore, struct Game *TempGame);
// Take data about Game(struct Game *TempGame)
// Displays scoreboard to the console


#endif