/*
** EPITECH PROJECT, 2024
** B-MUL-100-PAR-1-1-myradar-ariel.amriou
** File description:
** collision_planes.c
*/

#include "src.h"

static sfBool loop_is_same_zone(plane_t *plane1, plane_t *plane2, int i)
{
    for (int j = 0; j < NB_IDS_MAX && plane2->zone_ids[j] != -1; j++)
        if (plane1->zone_ids[i] == plane2->zone_ids[j])
            return sfTrue;
    return sfFalse;
}

static sfBool is_same_zone(plane_t *plane1, plane_t *plane2)
{
    for (int i = 0; i < NB_IDS_MAX && plane1->zone_ids[i] != -1; i++)
        if (loop_is_same_zone(plane1, plane2, i))
            return sfTrue;
    return sfFalse;
}

static int dot_product(sfVector2f v1, sfVector2f v2)
{
    return v1.x * v2.x + v1.y * v2.y;
}

static sfVector2f create_vector(sfVector2f a, sfVector2f b)
{
    sfVector2f vector = {b.x - a.x, b.y - a.y};

    return vector;
}

static sfBool check_dot_products(sfVector2f n,
    sfVector2f comparasion_point, sfVector2f points[NB_SIDES])
{
    sfVector2f vectors[NB_SIDES] = {0};

    for (size_t i = 0; i < NB_SIDES; i++) {
        vectors[i] = create_vector(comparasion_point, points[i]);
        if (dot_product(vectors[i], n) <= 0)
            return sfTrue;
    }
    return sfFalse;
}

static void check_collision(plane_t *planes, plane_t *i)
{
    sfBool i_destroy = sfFalse;

    for (plane_t *j = planes; j != NULL; j = j->next_plane) {
        if (j->is_landed || !j->is_spawned ||
            i->id == j->id || j->protected || !is_same_zone(i, j))
            continue;
        if (check_dot_products(j->vectors[0], j->sides[0], i->corners) &&
            check_dot_products(j->vectors[1], j->sides[1], i->corners) &&
            check_dot_products(j->vectors[2], j->sides[2], i->corners) &&
            check_dot_products(j->vectors[3], j->sides[3], i->corners) &&
            check_dot_products(i->vectors[0], i->sides[0], j->corners) &&
            check_dot_products(i->vectors[1], i->sides[1], j->corners) &&
            check_dot_products(i->vectors[2], i->sides[2], j->corners) &&
            check_dot_products(i->vectors[3], i->sides[3], j->corners)) {
            j->is_landed = sfTrue;
            i_destroy = sfTrue;
        }
    }
    if (i_destroy)
        i->is_landed = sfTrue;
}

void collision_planes(plane_t *planes)
{
    for (plane_t *i = planes; i != NULL; i = i->next_plane) {
        if (i->is_landed || !i->is_spawned || i->protected)
            continue;
        check_collision(planes, i);
    }
}
