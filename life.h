#ifndef LIFE_H
#define LIFE_H


#define FIELDS_PER_SIDE 20

typedef struct game_of_life {
    char fields[FIELDS_PER_SIDE][FIELDS_PER_SIDE];
} game_of_life;

// Return new instance of a game_of_life struct
game_of_life* game_of_life_new();

// Calculate next generation
void next_generation(game_of_life *game);

#endif /* LIFE_H */
