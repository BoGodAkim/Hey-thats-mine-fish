#ifndef PLACE
#define PLACE

void generate_seed2D(int size, float *value_array);
// Take size of seed(int size) and pointer of array for seed(float *value_array)
// This function generat seed and save it in (float *value_array)

void perlinNoise2D(int dimension, float *seed, int octaves, float bias, float *output);
// Take dimension(int dimension), seed (float *seed), octaves (int octaves), bias (float bias) and array in which save Perline noise (float *output)
// This function generate Perline noise and save it in (float *output)

int generate_map(struct Game *Game);
// Take data about Game(struct Game *Game)
// This function generate map and save it in (struct Game *Game)

void init_map(struct Game *Game);
// Take data about Game(struct Game *Game)
// This function generat board using fuction (creat_map) and print it using function (print_map) until is satisfied a result
// Function save the final map in Board and nothing return

void init_player_data(struct Game *Game);
// Take data about Game(struct Game *Game)
// This function take from each Player data about them or bot and save it in PlayerData
// This function returns nothing


#endif