/**
 * A simple game of life implementation written in C using Clutter.
 * Copyright (C) 2013 Danilo Bargen
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdlib.h>
#include <string.h>
#include "life.h"

int get_neighbor_count(game_of_life *game, int x, int y) {
    int count = 0;
    int max = FIELDS_PER_SIDE - 1;
    if (x > 0) {
        count += game->fields[x-1][y]; // west
        if (y > 0) count += game->fields[x-1][y-1]; // northwest
        if (y < max) count += game->fields[x-1][y+1]; // southwest
    }
    if (x < max) {
        count += game->fields[x+1][y]; // east
        if (y > 0) count += game->fields[x+1][y-1]; // northeast
        if (y < max) count += game->fields[x+1][y+1]; // southeast
    }
    if (y > 0) count += game->fields[x][y-1]; // north
    if (y < max) count += game->fields[x][y+1]; // south
    return count;
}

game_of_life* game_of_life_new() {
    // Create playing field with 2 dimensional array
    game_of_life *game = malloc(sizeof(game_of_life));

    // Initialize arrays with 0
    for (int i = 0; i < FIELDS_PER_SIDE; i++) {
        for (int j = 0; j < FIELDS_PER_SIDE; j++) {
            game->fields[i][j] = 0;
        }
    }

    return game;
}

void next_generation(game_of_life *game) {
    char *field;
    int neighbor_count;

    // Create snapshot of current game state
    game_of_life *snapshot = malloc(sizeof(*game));
    memcpy(snapshot, game, sizeof(*game));

    // Calculate life/death of fields
    for (int i = 0; i < FIELDS_PER_SIDE; i++) {
        for (int j = 0; j < FIELDS_PER_SIDE; j++) {
            field = &(game->fields[i][j]);
            neighbor_count = get_neighbor_count(snapshot, i, j);
            if (*field == 1) {
                if (neighbor_count < 2 || neighbor_count > 3) {
                    *field = 0;
                }
            } else {
                if (neighbor_count == 3) {
                    *field = 1;
                }
            }
        }
    }

    // Free memory
    free(snapshot);
}
