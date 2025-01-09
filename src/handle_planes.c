/*
** EPITECH PROJECT, 2024
** B-MUL-100-PAR-1-1-myradar-ariel.amriou
** File description:
** handle_planes.c
*/

#include "src.h"
#include <stdio.h>
#include <math.h>

static void vector_product(sfVector2f *v, sfVector2f speed, float x)
{
    v->x += speed.x * x;
    v->y += speed.y * x;
}

static void move_position(plane_t *plane, game_t *game)
{
    vector_product(&plane->pos, plane->speed,
        (game->timer->delta / MICROSEC_IN_SEC));
    for (size_t i = 0; i < NB_SIDES; i++) {
        vector_product(&plane->sides[i], plane->speed,
            (game->timer->delta / MICROSEC_IN_SEC));
        vector_product(&plane->corners[i], plane->speed,
            (game->timer->delta / MICROSEC_IN_SEC));
    }
}

static sfBool check_distances_point(sfVector2f point, tower_t *tower)
{
    float norm = 0;
    float x = 0;
    float y = 0;

    while (tower != NULL) {
        x = tower->pos.x - point.x;
        y = tower->pos.y - point.y;
        norm = sqrt(x * x + y * y);
        if (norm <= tower->radius)
            return sfTrue;
        tower = tower->next_tower;
    }
    return sfFalse;
}

static sfBool check_distances(plane_t *plane, tower_t *tower)
{
    if (check_distances_point(plane->pos, tower))
            return sfTrue;
    for (int i = 0; i < NB_SIDES; i++)
        if (check_distances_point(plane->sides[i], tower))
            return sfTrue;
    return sfFalse;
}

static void move_spawn_protect_planes(plane_t *plane,
    game_t *game, tower_t *tower)
{
    while (plane != NULL) {
        if (plane->is_spawned == sfFalse &&
            plane->is_landed == sfFalse &&
            plane->delay <= game->timer->sec) {
            plane->is_spawned = sfTrue;
            sfSprite_setPosition(plane->sprite, plane->pos);
            sfRectangleShape_setPosition(plane->hitbox, plane->pos);
        }
        if (plane->is_spawned == sfTrue && plane->is_landed == sfFalse) {
            move_position(plane, game);
            sfSprite_setPosition(plane->sprite, plane->pos);
            sfRectangleShape_setPosition(plane->hitbox, plane->pos);
        }
        if (check_distances(plane, tower))
            plane->protected = sfTrue;
        else
            plane->protected = sfFalse;
        plane = plane->next_plane;
    }
}

static void render_planes(plane_t *plane, game_t *game)
{
    while (plane != NULL) {
        if (plane->is_spawned == sfTrue && plane->is_landed == sfFalse
            && game->display_sprites == sfTrue)
            sfRenderWindow_drawSprite(game->render_window,
                plane->sprite, NULL);
        if (plane->is_spawned == sfTrue && plane->is_landed == sfFalse
            && game->display_hitbox == sfTrue)
            sfRenderWindow_drawRectangleShape(game->render_window,
                plane->hitbox, NULL);
        plane = plane->next_plane;
    }
}

static int is_landing(plane_t *plane)
{
    if (plane == NULL)
        return 0;
    if (plane->speed.x > 0 && plane->sides[0].x >= plane->end.x)
        return 1;
    if (plane->speed.x < 0 && plane->sides[0].x <= plane->end.x)
        return 1;
    if (plane->speed.y > 0 && plane->sides[0].y >= plane->end.y)
        return 1;
    if (plane->speed.y < 0 && plane->sides[0].y <= plane->end.y)
        return 1;
    return 0;
}

static void land_plane(plane_t *plane)
{
    while (plane != NULL) {
        if (is_landing(plane) == 1 && plane->is_landed == sfFalse)
            plane->is_landed = sfTrue;
        plane = plane->next_plane;
    }
}

static void are_all_landed(plane_t *plane, game_t *game)
{
    if (game->end_time != NOT_ALL_LANDED) {
        if (game->end_time + CLOSE_DELAY + (game->timer->t1 / MICROSEC_IN_SEC)
            <= game->timer->sec)
            sfRenderWindow_close(game->render_window);
        return;
    }
    while (plane != NULL) {
        if (plane->is_landed == sfFalse) {
            return;
        }
        plane = plane->next_plane;
    }
    game->end_time = game->timer->sec + (game->timer->t1 / MICROSEC_IN_SEC);
}

void handle_planes(plane_t *plane, game_t *game, tower_t *tower)
{
    move_spawn_protect_planes(plane, game, tower);
    collision_planes(plane);
    land_plane(plane);
    are_all_landed(plane, game);
    sort_planes(plane, game);
    render_planes(plane, game);
}
