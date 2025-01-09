/*
** EPITECH PROJECT, 2024
** B-MUL-100-PAR-1-1-myhunter-ariel.amriou
** File description:
** create_sprite.c
*/

#include "src.h"
#include "my.h"
#include <stdlib.h>

static int create_background(background_t **background)
{
    (*background) = malloc(sizeof(background_t));
    (*background)->sprite = sfSprite_create();
    (*background)->index_bg = DEFAULT_INDEX_BG;
    (*background)->sprite_texture[INDEX_BG1] =
        sfTexture_createFromFile(PATH_BG1, NULL);
    (*background)->sprite_texture[INDEX_BG2] =
        sfTexture_createFromFile(PATH_BG2, NULL);
    (*background)->sprite_texture[INDEX_BG3] =
        sfTexture_createFromFile(PATH_BG3, NULL);
    sfSprite_setTexture((*background)->sprite,
        (*background)->sprite_texture[DEFAULT_INDEX_BG], sfFalse);
    if (*background == NULL || (*background)->sprite == NULL ||
        (*background)->sprite_texture[0] == NULL ||
        (*background)->sprite_texture[1] == NULL ||
        (*background)->sprite_texture[2] == NULL)
        return 84;
    return 0;
}

static void create_all_sftexts(texts_t **texts)
{
    sfVector2f pos_time = {TXT_MARGIN, TXT_MARGIN};
    sfVector2f pos_fps = {300, TXT_MARGIN};

    sfText_setString((*texts)->time, (*texts)->time_txt);
    sfText_setPosition((*texts)->time, pos_time);
    sfText_setFont((*texts)->time, (*texts)->font);
    sfText_setString((*texts)->fps, (*texts)->fps_txt);
    sfText_setPosition((*texts)->fps, pos_fps);
    sfText_setFont((*texts)->fps, (*texts)->font);
}

static int create_texts(texts_t **texts)
{
    (*texts) = malloc(sizeof(texts_t));
    (*texts)->time = sfText_create();
    (*texts)->fps = sfText_create();
    (*texts)->time_txt = my_strdup("time :\n00:00");
    (*texts)->fps_txt = my_strdup("fps :\n000");
    (*texts)->font = sfFont_createFromFile(PATH_FONT);
    if ((*texts)->time == NULL || (*texts)->fps == NULL
        || (*texts)->font == NULL)
        return 84;
    create_all_sftexts(texts);
    return 0;
}

int create_game_sprites(game_sprites_t *sprites, char *pathname)
{
    if (create_background(&sprites->background) == 84
        || create_components(&sprites->planes,
        &sprites->towers, pathname) == 84
        || create_texts(&sprites->texts) == 84)
        return 84;
    return 0;
}
