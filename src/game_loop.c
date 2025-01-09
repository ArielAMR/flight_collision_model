/*
** EPITECH PROJECT, 2024
** B-MUL-100-PAR-1-1-myhunter-ariel.amriou
** File description:
** render.c
*/

#include "../include/src.h"
#include <time.h>
#include <stdlib.h>

static void render_background(background_t *background, game_t *game)
{
    sfRenderWindow_drawSprite
        (game->render_window, background->sprite, NULL);
}

static void render_towers(tower_t *tower, game_t *game)
{
    while (tower != NULL) {
        if (game->display_sprites)
            sfRenderWindow_drawSprite(game->render_window,
                tower->sprite, NULL);
        if (game->display_hitbox)
            sfRenderWindow_drawCircleShape(game->render_window,
                tower->hitbox, NULL);
        tower = tower->next_tower;
    }
}

static void change_time(texts_t *texts, game_t *game)
{
    int sec = game->timer->sec;
    int min = sec / 60;

    sec = sec % 60;
    if (min > 99)
        min = 99;
    texts->time_txt[TIME_TXT_OFFSET] = (min / 10) + '0';
    texts->time_txt[TIME_TXT_OFFSET + 1] = (min % 10) + '0';
    texts->time_txt[TIME_TXT_OFFSET + 3] = (sec / 10) + '0';
    texts->time_txt[TIME_TXT_OFFSET + 4] = (sec % 10) + '0';
    sfText_setString(texts->time, texts->time_txt);
}

static void change_fps(texts_t *texts, game_t *game)
{
    int fps = (1.0 / game->timer->delta) * MICROSEC_IN_SEC;

    if (fps < 100) {
        texts->fps_txt[FPS_TXT_OFFSET] = (fps / 10) + '0';
        texts->fps_txt[FPS_TXT_OFFSET + 1] = (fps % 10) + '0';
        texts->fps_txt[FPS_TXT_OFFSET + 2] = '\0';
        texts->fps_txt[FPS_TXT_OFFSET + 3] = '\0';
        sfText_setString(texts->fps, texts->fps_txt);
        return;
    }
    if (fps > 999)
        fps = 999;
    texts->fps_txt[FPS_TXT_OFFSET] = (fps / 100) + '0';
    texts->fps_txt[FPS_TXT_OFFSET + 1] = (fps / 10 % 10) + '0';
    texts->fps_txt[FPS_TXT_OFFSET + 2] = (fps % 10) + '0';
    texts->fps_txt[FPS_TXT_OFFSET + 3] = '\0';
    sfText_setString(texts->fps, texts->fps_txt);
}

static void render_texts(texts_t *texts, game_t *game)
{
    if (game->timer->t0 > game->timer->t1)
        change_time(texts, game);
    change_fps(texts, game);
    if (game->display_header) {
        sfRenderWindow_drawText(game->render_window, texts->time, NULL);
        sfRenderWindow_drawText(game->render_window, texts->fps, NULL);
    }
}

static void render_zones(zone_t *zone, game_t *game)
{
    while (zone != NULL) {
        if (game->display_zones)
            sfRenderWindow_drawRectangleShape(game->render_window,
                zone->hitbox, NULL);
        if (game->display_zones_txt)
            sfRenderWindow_drawText(game->render_window, zone->id_txt, NULL);
        zone = zone->next_zone;
    }
}

static void update_game_value(game_t *game)
{
    game->timer->t0 = game->timer->t1;
    game->timer->t1 = sfClock_getElapsedTime(game->timer->clock).microseconds;
    game->timer->delta = game->timer->t1 - game->timer->t0;
    if (game->timer->delta < 0)
        game->timer->delta += MICROSEC_IN_SEC;
}

void game_loop(game_sprites_t *sprites, game_t *game)
{
    while (sfRenderWindow_isOpen(game->render_window)) {
        poll_event(game, sprites->background);
        update_game_value(game);
        clock_function(game, sprites->planes);
        render_background(sprites->background, game);
        render_towers(sprites->towers, game);
        handle_planes(sprites->planes, game, sprites->towers);
        render_zones(*game->zones, game);
        render_texts(sprites->texts, game);
        sfRenderWindow_display(game->render_window);
        sfRenderWindow_clear(game->render_window, sfBlack);
    }
    destroy_all(sprites, game);
}
