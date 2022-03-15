#ifndef MAPGEN
#define MAPGEN

void generate_seed2D(int size, float *value_array);
// Take size of seed(int size) and pointer of array for seed(float *value_array)
// This function generat seed and save it in (float *value_array)

void perlinNoise2D(int dimension, float *seed, int octaves, float bias, float *output);
// Take dimension(int dimension), seed (float *seed), octaves (int octaves), bias (float bias) and array in which save Perline noise (float *output)
// This function generate Perline noise and save it in (float *output)

int generate_map(GameData *Game);
// Take data about Game(GameData *Game)
// This function generate map and save it in (GameData *Game)

#endif