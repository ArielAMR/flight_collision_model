/*
** EPITECH PROJECT, 2024
** B-MUL-100-PAR-1-1-myradar-ariel.amriou
** File description:
** quad_tree.c
*/

#include "src.h"
#include <stdlib.h>

static void put_zone(zone_t *zone,
    sfVector2f left_top, sfVector2f bottom_right)
{
    zone_t *new_zone = malloc(sizeof(zone_t));
    zone_t *tmp = zone->next_zone;

    new_zone->id_str = malloc(ID_CHARS);
    new_zone->id_txt = sfText_create();
    new_zone->hitbox = sfRectangleShape_create();
    new_zone->font = sfFont_createFromFile(PATH_FONT);
    if (new_zone == NULL || new_zone->hitbox == NULL
        || new_zone->id_str == NULL || new_zone->id_txt == NULL
        || new_zone->font == NULL)
        return;
    new_zone->next_zone = tmp;
    zone->next_zone = new_zone;
    new_zone->left_top = left_top;
    new_zone->id = 1;
    new_zone->number_planes = 0;
    new_zone->bottom_right = bottom_right;
    create_all_sfzone(new_zone);
}

static void split_zone(zone_t *zone_list)
{
    float left = zone_list->left_top.x;
    float top = zone_list->left_top.y;
    float right = zone_list->bottom_right.x;
    float bottom = zone_list->bottom_right.y;
    float mid_x = (right - left) / 2 + left;
    float mid_y = (bottom - top) / 2 + top;

    put_zone(zone_list, (sfVector2f){mid_x, mid_y},
        (sfVector2f){right, bottom});
    put_zone(zone_list, (sfVector2f){left, mid_y},
        (sfVector2f){mid_x, bottom});
    put_zone(zone_list, (sfVector2f){mid_x, top},
        (sfVector2f){right, mid_y});
    change_zone(zone_list, (sfVector2f){left, top},
        (sfVector2f){mid_x, mid_y});
}

int quad_tree(game_t *game, plane_t *plane)
{
    zone_t *zone = *game->zones;
    int count = 0;

    while (zone != NULL) {
        if (zone->number_planes >= SPLIT_CAP &&
            zone->bottom_right.x - zone->left_top.x >= MIN_ZONE_SIZE) {
            split_zone(zone);
            sort_id(*game->zones);
            count++;
        }
        zone = zone->next_zone;
    }
    if (count != 0) {
        sort_planes(plane, game);
        quad_tree(game, plane);
    }
    return 0;
}
