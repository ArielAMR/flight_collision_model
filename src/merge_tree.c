/*
** EPITECH PROJECT, 2024
** B-MUL-100-PAR-1-1-myradar-ariel.amriou
** File description:
** merge_tree.c
*/

#include "src.h"

static sfBool is_four_zones(zone_t *zone)
{
    if (zone != NULL &&
        zone->next_zone != NULL &&
        zone->next_zone->next_zone != NULL &&
        zone->next_zone->next_zone->next_zone != NULL)
        return sfTrue;
    return sfFalse;
}

static sfBool is_merge(zone_t *zone1)
{
    zone_t *zone2 = zone1->next_zone;
    zone_t *zone3 = zone2->next_zone;
    zone_t *zone4 = zone3->next_zone;
    float len1 = zone1->bottom_right.x - zone1->left_top.x;
    float len2 = zone2->bottom_right.x - zone2->left_top.x;
    float len3 = zone3->bottom_right.x - zone3->left_top.x;
    float len4 = zone4->bottom_right.x - zone4->left_top.x;
    int total_planes = zone1->number_planes + zone2->number_planes +
        zone3->number_planes + zone4->number_planes;

    if (total_planes < MERGE_CAP &&
        len1 == len2 && len1 == len3 && len1 == len4 &&
        zone1->bottom_right.x == zone2->left_top.x &&
        zone3->bottom_right.x == zone4->left_top.x &&
        zone1->bottom_right.y == zone3->left_top.y &&
        zone2->bottom_right.y == zone4->left_top.y &&
        zone1->left_top.x == zone3->left_top.x &&
        zone1->left_top.y == zone2->left_top.y)
        return sfTrue;
    return sfFalse;
}

static void merge(zone_t *zone1)
{
    zone_t *zone2 = zone1->next_zone;
    zone_t *zone3 = zone2->next_zone;
    zone_t *zone4 = zone3->next_zone;

    change_zone(zone1, zone1->left_top, zone4->bottom_right);
    zone1->next_zone = zone4->next_zone;
    destroy_zone(zone2);
    destroy_zone(zone3);
    destroy_zone(zone4);
}

void merge_tree(game_t *game)
{
    zone_t *zone = *game->zones;

    while (is_four_zones(zone)) {
        if (is_merge(zone)) {
            merge(zone);
            sort_id(*game->zones);
        }
        zone = zone->next_zone;
    }
}
