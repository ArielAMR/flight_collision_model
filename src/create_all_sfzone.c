/*
** EPITECH PROJECT, 2024
** B-MUL-100-PAR-1-1-myradar-ariel.amriou
** File description:
** create_all_sfzone.c
*/

#include "src.h"
#include <stdlib.h>
#include <time.h>

void create_all_sfzone(zone_t *zone)
{
    sfVector2f size =
        {zone->bottom_right.x - zone->left_top.x - (ZONE_THICKNESS * 2),
        zone->bottom_right.y - zone->left_top.y - (ZONE_THICKNESS * 2)};
    sfVector2f origin =
        {zone->left_top.x + ZONE_THICKNESS,
        zone->left_top.y + ZONE_THICKNESS};

    sfRectangleShape_setPosition(zone->hitbox, origin);
    sfRectangleShape_setSize(zone->hitbox, size);
    sfRectangleShape_setFillColor(zone->hitbox, sfTransparent);
    sfRectangleShape_setOutlineColor(zone->hitbox, sfColor_fromRGB(
        rand() % RGB_MAX + 1,
        rand() % RGB_MAX + 1,
        rand() % RGB_MAX + 1));
    sfRectangleShape_setOutlineThickness(zone->hitbox, ZONE_THICKNESS);
    sfText_setFont(zone->id_txt, zone->font);
    sfText_setPosition(zone->id_txt, zone->left_top);
}

void destroy_zone(zone_t *zone)
{
    sfRectangleShape_destroy(zone->hitbox);
    sfFont_destroy(zone->font);
    sfText_destroy(zone->id_txt);
    free(zone->id_str);
    free(zone);
}
