/*
** EPITECH PROJECT, 2024
** B-MUL-100-PAR-1-1-myradar-ariel.amriou
** File description:
** puttower.c
*/

#include "my.h"
#include "src.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

static void create_all_sftower(tower_t *new)
{
    sfVector2f origin = {TOWER_WIDTH / 2, TOWER_HEIGHT};
    sfVector2f offset_hitbox = {new->radius, new->radius};

    sfSprite_setTexture(new->sprite, new->sprite_texture, sfFalse);
    sfSprite_setOrigin(new->sprite, origin);
    sfSprite_setPosition(new->sprite, new->pos);
    sfCircleShape_setPosition(new->hitbox, new->pos);
    sfCircleShape_setRadius(new->hitbox, new->radius);
    sfCircleShape_setOutlineThickness(new->hitbox, 1);
    sfCircleShape_setFillColor(new->hitbox, sfTransparent);
    sfCircleShape_setOrigin(new->hitbox, offset_hitbox);
}

static void populate_tower(char **list, tower_t *new)
{
    new->pos.x = my_getnbr(list[1]);
    new->pos.y = my_getnbr(list[2]);
    new->radius = my_getnbr(list[3]);
}

static int create_tower(tower_t *new)
{
    new->sprite_texture = sfTexture_createFromFile(PATH_TOWER, NULL);
    new->sprite = sfSprite_create();
    new->hitbox = sfCircleShape_create();
    if (new->sprite == NULL || new->sprite_texture == NULL
        || new->hitbox == NULL)
        return 84;
    create_all_sftower(new);
    return 0;
}

int puttower(tower_t **tower, char *buff)
{
    tower_t *new = malloc(sizeof(tower_t));
    char **list = my_str_to_word_array(buff);

    if (new == NULL || list_len(list) != 4 ||
        are_all_numbers(list, 1, 3))
        return 84;
    populate_tower(list, new);
    if (create_tower(new) == 84)
        return 84;
    new->next_tower = *tower;
    *tower = new;
    free_list(list);
    return 0;
}
