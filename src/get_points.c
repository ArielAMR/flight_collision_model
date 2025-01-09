/*
** EPITECH PROJECT, 2024
** B-MUL-100-PAR-1-1-myradar-ariel.amriou
** File description:
** get_points.c
*/

#include "src.h"
#include <math.h>

static sfVector2f vector_sum(sfVector2f v1, sfVector2f v2)
{
    sfVector2f sum = {v1.x + v2.x, v1.y + v2.y};

    return sum;
}

static void get_vectors(plane_t *plane)
{
    float rad = RAD(plane->rotation_degrees);

    plane->vectors[0].x = (PLANE_WIDTH / 2) * cos(rad);
    plane->vectors[0].y = (PLANE_HEIGHT / 2) * sin(rad);
    for (size_t i = 1; i < NB_SIDES; i++) {
        plane->vectors[i].x = - plane->vectors[i - 1].y;
        plane->vectors[i].y = plane->vectors[i - 1].x;
    }
}

static void get_sides(plane_t *plane)
{
    for (size_t i = 0; i < NB_SIDES; i++)
        plane->sides[i] = vector_sum(plane->vectors[i], plane->pos);
}

static void get_corners(plane_t *plane)
{
    for (size_t i = 0; i < NB_SIDES; i++)
        plane->corners[i] = vector_sum(vector_sum(plane->vectors[i],
            plane->vectors[(i + 1) % NB_SIDES]), plane->pos);
}

void get_points(plane_t *plane)
{
    get_vectors(plane);
    get_sides(plane);
    get_corners(plane);
}
