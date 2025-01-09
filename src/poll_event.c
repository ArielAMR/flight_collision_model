/*
** EPITECH PROJECT, 2024
** B-MUL-100-PAR-1-1-myradar-ariel.amriou
** File description:
** poll_event.c
*/

#include "src.h"

static void is_hitboxes(game_t *game, sfBool shift)
{
    if (sfKeyboard_isKeyPressed(sfKeyL) && shift)
        game->display_hitbox = sfFalse;
    if (sfKeyboard_isKeyPressed(sfKeyL) && !shift)
        game->display_hitbox = sfTrue;
}

static void is_sprites(game_t *game, sfBool shift)
{
    if (sfKeyboard_isKeyPressed(sfKeyS) && shift)
        game->display_sprites = sfFalse;
    if (sfKeyboard_isKeyPressed(sfKeyS) && !shift)
        game->display_sprites = sfTrue;
}

static void is_header(game_t *game, sfBool shift)
{
    if (sfKeyboard_isKeyPressed(sfKeyT) && shift)
        game->display_header = sfFalse;
    if (sfKeyboard_isKeyPressed(sfKeyT) && !shift)
        game->display_header = sfTrue;
}

static void is_zone(game_t *game, sfBool shift)
{
    if (sfKeyboard_isKeyPressed(sfKeyZ) && shift) {
        game->display_zones_txt = sfFalse;
        game->display_zones = sfFalse;
    }
    if (sfKeyboard_isKeyPressed(sfKeyZ) && !shift) {
        game->display_zones_txt = sfTrue;
        game->display_zones = sfTrue;
    }
}

static void is_zone_txt(game_t *game, sfBool shift)
{
    if (sfKeyboard_isKeyPressed(sfKeyP) && shift)
        game->display_zones_txt = sfFalse;
    if (sfKeyboard_isKeyPressed(sfKeyP) && !shift && game->display_zones)
        game->display_zones_txt = sfTrue;
}

static void is_background(background_t *background)
{
    if (sfKeyboard_isKeyPressed(sfKeyB)) {
        background->index_bg++;
        if (background->index_bg == NB_BG)
            background->index_bg = 0;
        sfSprite_setTexture(background->sprite,
            background->sprite_texture[background->index_bg], sfFalse);
    }
}

static void handle_input(game_t *game, background_t *background)
{
    sfBool shift = sfKeyboard_isKeyPressed(sfKeyLShift);

    is_hitboxes(game, shift);
    is_sprites(game, shift);
    is_header(game, shift);
    is_zone(game, shift);
    is_zone_txt(game, shift);
    is_background(background);
}

void poll_event(game_t *game, background_t *background)
{
    while (sfRenderWindow_pollEvent(game->render_window, &game->event)) {
        if (game->event.type == sfEvtClosed
            || (sfKeyboard_isKeyPressed(sfKeyD)
            && sfKeyboard_isKeyPressed(sfKeyLControl))
            || sfKeyboard_isKeyPressed(sfKeyEscape))
            sfRenderWindow_close(game->render_window);
        handle_input(game, background);
    }
}
