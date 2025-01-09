/*
** EPITECH PROJECT, 2024
** B-MUL-100-PAR-1-1-myradar-ariel.amriou
** File description:
** putplane.c
*/

#include "my.h"
#include "src.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

static float get_rotation(sfVector2f *pos, sfVector2f *end)
{
    float x = end->x - pos->x;
    float y = end->y - pos->y;
    float rad = atan(fabs(y) / fabs(x));

    if (x < 0 && y < 0)
        rad += M_PI;
    if (x < 0 && y > 0)
        rad = ((3 * M_PI) / 2) + (((3 * M_PI) / 2) - rad);
    if (x > 0 && y < 0)
        rad *= -1;
    return DEG(rad);
}

static sfVector2f get_speed_vector(int speed, plane_t *new)
{
    float x = new->end.x - new->pos.x;
    float y = new->end.y - new->pos.y;
    float norm = sqrt(pow(x, 2) + pow(y, 2));
    float time = norm / speed;
    sfVector2f speed_vector = {x / time, y / time};

    return speed_vector;
}

static void populate_plane(char **list, plane_t *new)
{
    new->pos.x = my_getnbr(list[1]);
    new->pos.y = my_getnbr(list[2]);
    new->end.x = my_getnbr(list[3]);
    new->end.y = my_getnbr(list[4]);
    new->speed = get_speed_vector(my_getnbr(list[5]), new);
    new->delay = my_getnbr(list[6]);
    new->is_spawned = sfFalse;
    new->is_landed = sfFalse;
    new->protected = sfTrue;
}

static void create_all_sfplane(plane_t *new)
{
    sfVector2f origin = {PLANE_WIDTH / 2, PLANE_HEIGHT / 2};
    sfVector2f hitbox_size = {PLANE_WIDTH, PLANE_HEIGHT};

    sfSprite_setTexture(new->sprite, new->sprite_texture, sfFalse);
    sfSprite_setOrigin(new->sprite, origin);
    sfSprite_setRotation(new->sprite, new->rotation_degrees);
    sfRectangleShape_setSize(new->hitbox, hitbox_size);
    sfRectangleShape_setOutlineColor(new->hitbox, sfRed);
    sfRectangleShape_setOutlineThickness(new->hitbox, 1);
    sfRectangleShape_setOrigin(new->hitbox, origin);
    sfRectangleShape_setRotation(new->hitbox, new->rotation_degrees);
    sfRectangleShape_setFillColor(new->hitbox, sfTransparent);
}

static int create_plane(plane_t *new)
{
    new->rotation_degrees = get_rotation(&new->pos, &new->end);
    new->sprite_texture = sfTexture_createFromFile(PATH_PLANE, NULL);
    new->sprite = sfSprite_create();
    new->hitbox = sfRectangleShape_create();
    if (new->sprite == NULL || new->sprite_texture == NULL
        || new->hitbox == NULL)
        return 84;
    get_points(new);
    create_all_sfplane(new);
    return 0;
}

int putplane(plane_t **plane, char *buff)
{
    plane_t *new = malloc(sizeof(plane_t));
    char **list = my_str_to_word_array(buff);

    if (new == NULL || list_len(list) != 7 ||
        are_all_numbers(list, 1, 6))
        return 84;
    populate_plane(list, new);
    if (create_plane(new) == 84)
        return 84;
    for (int i = 0; i < NB_IDS_MAX; i++)
        new->zone_ids[i] = -1;
    new->id = 0;
    if (*plane != NULL)
        new->id = (*plane)->id + 1;
    new->next_plane = *plane;
    *plane = new;
    free_list(list);
    return 0;
}
