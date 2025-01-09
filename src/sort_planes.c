/*
** EPITECH PROJECT, 2024
** B-MUL-100-PAR-1-1-myradar-ariel.amriou
** File description:
** sort_planes.c
*/

#include "src.h"

static void id_to_plane(plane_t *plane, int id)
{
    int i = 0;

    while (i < NB_IDS_MAX && plane->zone_ids[i] != -1)
        i++;
    if (i >= NB_IDS_MAX)
        return;
    plane->zone_ids[i] = id;
}

static void reset_ids(plane_t *plane)
{
    for (int i = 0; i < NB_IDS_MAX; i++)
        plane->zone_ids[i] = -1;
}

static sfBool point_is_in_zone(sfVector2f point, zone_t *zone)
{
    if (point.x >= zone->left_top.x &&
        point.x <= zone->bottom_right.x &&
        point.y >= zone->left_top.y &&
        point.y <= zone->bottom_right.y)
        return sfTrue;
    return sfFalse;
}

static void is_in_zone(plane_t *plane, zone_t *zone)
{
    if (!plane->is_landed && plane->is_spawned &&
    (point_is_in_zone(plane->corners[0], zone) ||
    point_is_in_zone(plane->corners[1], zone) ||
    point_is_in_zone(plane->corners[2], zone) ||
    point_is_in_zone(plane->corners[3], zone))) {
        id_to_plane(plane, zone->id);
        zone->number_planes++;
    }
}

void sort_planes(plane_t *plane, game_t *game)
{
    zone_t *zones1 = *game->zones;
    zone_t *zones2 = *game->zones;

    while (zones1 != NULL) {
        zones1->number_planes = 0;
        zones1 = zones1->next_zone;
    }
    while (plane != NULL) {
        reset_ids(plane);
        while (zones2 != NULL) {
            is_in_zone(plane, zones2);
            zones2 = zones2->next_zone;
        }
        zones2 = *game->zones;
        plane = plane->next_plane;
    }
}
