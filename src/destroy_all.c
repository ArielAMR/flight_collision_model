/*
** EPITECH PROJECT, 2024
** B-MUL-100-PAR-1-1-myradar-ariel.amriou
** File description:
** destroy_all.c
*/

#include "src.h"
#include <stdlib.h>

static void destroy_planes(plane_t *plane)
{
    plane_t *tmp = NULL;

    while (plane != NULL) {
        tmp = plane;
        plane = plane->next_plane;
        sfTexture_destroy(tmp->sprite_texture);
        sfSprite_destroy(tmp->sprite);
        sfRectangleShape_destroy(tmp->hitbox);
        free(tmp);
    }
}

static void destroy_towers(tower_t *tower)
{
    tower_t *tmp = NULL;

    while (tower != NULL) {
        tmp = tower;
        tower = tower->next_tower;
        sfTexture_destroy(tmp->sprite_texture);
        sfSprite_destroy(tmp->sprite);
        sfCircleShape_destroy(tmp->hitbox);
        free(tmp);
    }
}

static void destroy_background(background_t *background)
{
    sfSprite_destroy(background->sprite);
    sfTexture_destroy(background->sprite_texture[0]);
    sfTexture_destroy(background->sprite_texture[1]);
    sfTexture_destroy(background->sprite_texture[2]);
    free(background);
}

static void destroy_timer(time_content_t *timer)
{
    sfClock_destroy(timer->clock);
    free(timer);
}

static void destroy_texts(texts_t *texts)
{
    sfText_destroy(texts->time);
    sfText_destroy(texts->fps);
    sfFont_destroy(texts->font);
    free(texts->time_txt);
    free(texts->fps_txt);
    free(texts);
}

static void destroy_zones(zone_t *zone)
{
    zone_t *tmp = NULL;

    while (zone != NULL) {
        tmp = zone;
        zone = zone->next_zone;
        destroy_zone(tmp);
    }
}

void destroy_all(game_sprites_t *sprites, game_t *game)
{
    destroy_planes(sprites->planes);
    destroy_towers(sprites->towers);
    destroy_background(sprites->background);
    destroy_timer(game->timer);
    destroy_texts(sprites->texts);
    destroy_zones(*game->zones);
    sfRenderWindow_destroy(game->render_window);
}
