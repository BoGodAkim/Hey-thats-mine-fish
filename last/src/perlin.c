#include <stdlib.h>
// #include "perlin.h"
#include <time.h>



void generate_seed(int size, float* value_array)
{
    for(int i = 0; i < size; i++)
    {
        value_array[i] = (float) rand() / (float) RAND_MAX;
    }
}
void generate_seed2D(int size, float* value_array)
{
    time_t t;
    int seed = time(&t);
    srand(seed);
    for(int i = 0; i < size*size; i++)
    {
        value_array[i] = (float) rand() / (float) RAND_MAX;
    }
}

void perlinNoise1D(int count, float* seed, int octaves, float bias, float* output)
{
    for (int i = 0; i < count; i++)
    {
        float noise = 0.0f;
        float scale = 1.0f;
        float scale_acc = 0.0f;

        for (int o = 0; o < octaves; o++)
        {
            int pitch = count >> o;
            int sample1 = (i / pitch) * pitch;
            int sample2 = (sample1 + pitch) % count;

            float blend = (float)(i - sample1) / (float) pitch;
            float sample = (1.0f - blend) * seed[sample1] + blend * seed[sample2];

            noise += sample * scale;
            scale_acc += scale;
            scale = scale / bias;
        }

        output[i] = noise / scale_acc;
        
    }
    
}

void perlinNoise2D(int dimension, float* seed, int octaves, float bias, float* output)
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

                float blendX = (float)(x - sample1X) / (float) pitch;
                float blendY = (float)(y - sample1Y) / (float) pitch;

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