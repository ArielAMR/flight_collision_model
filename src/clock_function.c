/*
** EPITECH PROJECT, 2024
** B-MUL-100-PAR-1-1-myhunter-ariel.amriou
** File description:
** clock_function.c
*/

#include "../include/src.h"
#include <time.h>

void clock_function(game_t *game, plane_t *plane)
{
    if (sfClock_getElapsedTime(game->timer->clock).microseconds
        >= CLOCK_SPEED) {
        sfClock_restart(game->timer->clock);
        game->timer->sec++;
        quad_tree(game, plane);
        merge_tree(game);
    }
}
