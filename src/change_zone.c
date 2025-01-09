/*
** EPITECH PROJECT, 2024
** B-MUL-100-PAR-1-1-myradar-ariel.amriou
** File description:
** change_zone.c
*/

#include "src.h"

void change_zone(zone_t *zone,
    sfVector2f top_left, sfVector2f bottom_right)
{
    sfVector2f size = {0};

    zone->left_top = top_left;
    zone->id = 0;
    zone->number_planes = 0;
    zone->bottom_right = bottom_right;
    size.x = zone->bottom_right.x - zone->left_top.x - (ZONE_THICKNESS * 2);
    size.y = zone->bottom_right.y - zone->left_top.y - (ZONE_THICKNESS * 2);
    sfRectangleShape_setSize(zone->hitbox, size);
}
