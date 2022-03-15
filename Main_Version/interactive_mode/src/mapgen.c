#include "perlin.c"
// #include "mapgen.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

#define NOISE_SIZE 256
float seed[NOISE_SIZE * NOISE_SIZE];
float noiseValues[NOISE_SIZE * NOISE_SIZE];
void initializeNoise()
{
    generate_seed2D(NOISE_SIZE, seed);
    perlinNoise2D(NOISE_SIZE, seed, 8, 0.5f, noiseValues);
}

float noise(int x, int y)
{
    return noiseValues[x * NOISE_SIZE + y];
}
int generate_map(struct Game *TempGame)
{
    int count = 0;
    initializeNoise();

    for (int x = 1; x < TempGame->SizeMapX + 1; x++)
    {
        for (int y = 1; y < TempGame->SizeMapY + 1; y++)
        {
            int radius = sqrt(pow(x, 2) + pow(y, 2));
            float u = 2.0f * (float)x / (float)TempGame->SizeMapX - 1.0f;
            float v = 2.0f * (float)y / (float)TempGame->SizeMapX - 1.0f;
            float ds = u * u + v * v;

            if (noise(x, y) > 0.3 + 0.2 * ds)
            {
                int fish_amount = ((float)rand() / (float)RAND_MAX) * 3.0f;
                TempGame->Map[x][y].Fish = fish_amount == 0 ? 3 : fish_amount;
            }
            else
                TempGame->Map[x][y].Fish = 0;

            if (TempGame->Map[x][y].Fish == 1)
            {
                count++;
            }
        }
    }
    return count;
}