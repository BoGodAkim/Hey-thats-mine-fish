// #include <stdlib.h>
// #include <time.h>
// #include "struct.h"
// #include "mapgen.h"

#define NOISE_SIZE 256
float seed[NOISE_SIZE * NOISE_SIZE];
float noiseValues[NOISE_SIZE * NOISE_SIZE];

void generate_seed2D(int size, float *value_array)
{
    time_t t;
    int seed = time(&t);
    srand(seed);
    for (int i = 0; i < size * size; i++)
    {
        value_array[i] = (float)rand() / (float)RAND_MAX;
    }
}

void perlinNoise2D(int dimension, float *seed, int octaves, float bias, float *output)
{
    for (int x = 0; x < dimension; x++)
    {
        for (int y = 0; y < dimension; y++)
        {
            float noise = 0.0f;
            float scale = 1.0f;
            float scale_acc = 0.0f;

            for (int o = 0; o < octaves; o++)
            {
                int pitch = dimension >> o;
                int sample1X = (x / pitch) * pitch;
                int sample1Y = (y / pitch) * pitch;
                int sample2X = (sample1X + pitch) % dimension;
                int sample2Y = (sample1Y + pitch) % dimension;

                float blendX = (float)(x - sample1X) / (float)pitch;
                float blendY = (float)(y - sample1Y) / (float)pitch;

                float sampleX = (1.0f - blendX) * seed[sample1Y * dimension + sample1X] + blendX * seed[sample1Y * dimension + sample2X];
                float sampleY = (1.0f - blendX) * seed[sample2Y * dimension + sample1X] + blendX * seed[sample2Y * dimension + sample2X];

                noise += (blendY * (sampleY - sampleX) + sampleX) * scale;
                scale_acc += scale;
                scale = scale / bias;
            }

            output[y * dimension + x] = noise / scale_acc;
        }
    }
}


int generate_map(GameData *Game)
{
    int count = 0;
    generate_seed2D(NOISE_SIZE, seed);
    perlinNoise2D(NOISE_SIZE, seed, 8, 0.5f, noiseValues);

    for (int x = 1; x < Game->boardWidth + 1; x++)
    {
        for (int y = 1; y < Game->boardHeight + 1; y++)
        {
            int radius = sqrt(pow(x, 2) + pow(y, 2));
            float u = 2.0f * (float)x / (float)Game->boardWidth - 1.0f;
            float v = 2.0f * (float)y / (float)Game->boardHeight - 1.0f;
            float ds = u * u + v * v;

            if (noiseValues[x * NOISE_SIZE + y] > 0.3 + 0.2 * ds)
            {
                int fish_amount = rand() % 3 +1;
                Game->Board[x][y].Fish = fish_amount;
            }
            else
                Game->Board[x][y].Fish = 0;

            if (Game->Board[x][y].Fish == 1)
            {
                count++;
            }
        }
    }
    return count;
}