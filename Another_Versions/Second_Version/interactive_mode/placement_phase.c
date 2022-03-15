//#include "placement_phase.h"

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

int generate_map(struct Game *Game)
{
    int NOISE_SIZE = 256;
    float seed[NOISE_SIZE * NOISE_SIZE];
    float noiseValues[NOISE_SIZE * NOISE_SIZE];
    int count = 0;
    generate_seed2D(NOISE_SIZE, seed);
    perlinNoise2D(NOISE_SIZE, seed, 8, 0.5f, noiseValues);

    for (int x = 1; x < Game->SizeMapX + 1; x++)
    {
        for (int y = 1; y < Game->SizeMapY + 1; y++)
        {
            int radius = sqrt(pow(x, 2) + pow(y, 2));
            float u = 2.0f * (float)x / (float)Game->SizeMapX - 1.0f;
            float v = 2.0f * (float)y / (float)Game->SizeMapY - 1.0f;
            float ds = u * u + v * v;

            if (noiseValues[x * NOISE_SIZE + y] > 0.3 + 0.2 * ds)
            {
                int fish_amount = rand() % 3 + 1;
                Game->Map[x][y].Fish = fish_amount;
            }
            else
                Game->Map[x][y].Fish = 0;

            if (Game->Map[x][y].Fish == 1)
            {
                count++;
            }
        }
    }
    return count;
}

void init_map(struct Game *Game)
{
    char Answer[20];
    do
    {
        while (generate_map(Game) <= Game->NumPlayers * Game->NumPenguins)
        {
        }
        print_map(Game);
        printf("Do you want to change the map(Y/N)\n");
        scanf("%s", Answer);
        while (!((Answer[0] == 'Y' && strlen(Answer) == 1) || (Answer[0] == 'N' && strlen(Answer) == 1)))
        {
            printf("Invalid answer.\nEnter correct answer:");
            scanf("%s", Answer);
        }
    } while (Answer[0] == 'Y' && strlen(Answer) == 1);
}
void init_player_data(struct Game *Game)
{
    int *OrderCheck, NameUnitCheck[300], *RandomOrder, RandomNumber, BotCounter = 0, RandomOrderBool;
    char Answer[20];
    OrderCheck = (int *)calloc(Game->NumPlayers, sizeof(int));
    RandomOrder = (int *)calloc(Game->NumPlayers, sizeof(int));
    for (int i = 0; i < Game->NumPlayers; i++)
    {
        RandomOrder[i] = i;
    }
    for (int i = 0; i < 300; i++)
    {
        NameUnitCheck[i] = 0;
    }
    printf("Choose turn order - randomly or manually (R/M):");
    scanf("%s", &Answer);
    while (strlen(Answer) != 1 || (Answer[0] != 'R' && Answer[0] != 'M'))
    {
        printf("Invalid answer.\nEnter correct answer:");
        scanf("%s", &Answer);
    }
    if (Answer[0] == 'R')
    {
        RandomOrderBool = 1;
    }
    else
    {
        RandomOrderBool = 0;
    }
    for (int i = 0; i < Game->NumPlayers; i++)
    {
        printf("Player number %d, enter the nickname of Player:", i + 1);
        scanf("%s", &Game->Player[i].Name);
        while (check_names(i, Game) == 1)
        {
            printf("Invalid name.\nYour name can't be the same as another players'.\nEnter the name:");
            scanf("%s", &Game->Player[i].Name);
        }
        printf("Enter the name of the penguins (You can choose any one character):");
        scanf("%c", &Game->Player[i].NameUnit);
        scanf("%c", &Game->Player[i].NameUnit);
        while ((Game->Player[i].NameUnit >= '0' && Game->Player[i].NameUnit <= '9') || NameUnitCheck[Game->Player[i].NameUnit] == 1)
        {
            printf("Invalid character.\nYou can use any one character and the character can't be the same as another players.\nEnter the name of the penguins (You can choose any one character except numbers):");
            scanf("%c", &Game->Player[i].NameUnit);
            scanf("%c", &Game->Player[i].NameUnit);
        }
        NameUnitCheck[Game->Player[i].NameUnit] = 1;
        if (RandomOrderBool == 1)
        {
            RandomNumber = rand() % (Game->NumPlayers - i);
            Game->Order[RandomOrder[RandomNumber]] = i;
            printf("Player %s (%c) moves %d.\n", Game->Player[i].Name, Game->Player[i].NameUnit, RandomOrder[RandomNumber] + 1);
            RandomOrder[RandomNumber] = RandomOrder[Game->NumPlayers - i - 1];
        }
        else
        {
            printf("Choose turn from 1 to %d:", Game->NumPlayers);
            scanf("%d", &RandomNumber);
            while (RandomNumber > Game->NumPlayers || RandomNumber <= 0 || OrderCheck[RandomNumber - 1] == 1)
            {
                printf("Invald turn.\nYou can use numbers from 1 to %d and turn can't be the same as another players'.\nChoose turn from 1 to %d:", Game->NumPlayers, Game->NumPlayers);
                scanf("%d", &RandomNumber);
            }
            Game->Order[RandomNumber - 1] = i;
            OrderCheck[RandomNumber - 1] = 1;
            RandomOrder[RandomNumber - 1] = RandomOrder[Game->NumPlayers - i - 1];
        }
    }
    free(OrderCheck);
    free(RandomOrder);
}