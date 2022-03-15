#ifndef DISP
#define DISP

void print_map(struct Game *Game);
// Take data about Game(struct Game *Game)
// Prints map to the console

void sort_score(int NumPlayer, int *Score, int *PlayerScore);
// Take data about Game(struct Game *Game)
// Sort score for displaying in the console

void print_scoreboard(int *Score, int *PlayerScore, struct Game *Game);
// Take data about Game(struct Game *Game)
// Displays scoreboard to the console

#endif