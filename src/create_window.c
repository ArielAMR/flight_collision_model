/*
** EPITECH PROJECT, 2024
** B-MUL-100-PAR-1-1-myhunter-ariel.amriou
** File description:
** create_window.c
*/

#include "src.h"
#include <stdlib.h>

static sfRenderWindow *create_renderwindow(unsigned int x,
    unsigned int y, unsigned int bpp, char *title)
{
    sfVideoMode video_mode = {x, y, bpp};

    return (sfRenderWindow_create(video_mode,
        title, DISPLAY_MODE, NULL));
}

static int create_timer(time_content_t **timer)
{
    (*timer) = malloc(sizeof(time_content_t));
    (*timer)->delta = 0;
    (*timer)->t0 = 0;
    (*timer)->t1 = 0;
    (*timer)->clock = sfClock_create();
    (*timer)->sec = 0;
    if (*timer == NULL)
        return 84;
    return 0;
}

static int create_zone(zone_t ***zone)
{
    *zone = malloc(sizeof(zone_t *));
    **zone = malloc(sizeof(zone_t));
    (**zone)->id_str = malloc(ID_CHARS);
    (**zone)->id_txt = sfText_create();
    (**zone)->hitbox = sfRectangleShape_create();
    (**zone)->font = sfFont_createFromFile(PATH_FONT);
    if (*zone == NULL || **zone == NULL ||
        (**zone)->id_str == NULL || (**zone)->font == NULL ||
        (**zone)->hitbox == NULL || (**zone)->id_txt == NULL)
        return 84;
    (**zone)->left_top.x = 0;
    (**zone)->left_top.y = 0;
    (**zone)->bottom_right.x = BG_WIDTH;
    (**zone)->bottom_right.y = BG_HEIGHT;
    (**zone)->id = 1;
    (**zone)->number_planes = 0;
    (**zone)->next_zone = NULL;
    create_all_sfzone(**zone);
    return 0;
}

int create_window(game_t *game)
{
    game->render_window = create_renderwindow(1920, 1080, 32, "my_radar");
    sfRenderWindow_setFramerateLimit(game->render_window, FRAMERATE);
    game->window_size = sfRenderWindow_getSize(game->render_window);
    game->display_hitbox = DEFAULT_HITBOX;
    game->display_sprites = DEFAULT_SPRITE;
    game->display_header = DEFAULT_HEADER;
    game->display_zones = DEFAULT_ZONE;
    game->display_zones_txt = DEFAULT_ZONE_TXT;
    game->end_time = NOT_ALL_LANDED;
    if (create_zone(&game->zones) == 84 ||
        create_timer(&game->timer) == 84)
        return 84;
    return 0;
}
