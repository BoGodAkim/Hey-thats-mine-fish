#pragma once

void perlinNoise1D(int count, float* seed, int octaves, float bias, float* output);
void perlinNoise2D(int size, float* seed, int octaves, float bias, float* output);
void generate_seed(int size, float* value_array);
void generate_seed2D(int size, float* value_array);