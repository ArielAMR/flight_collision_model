/*
** EPITECH PROJECT, 2024
** B-MUL-100-PAR-1-1-myhunter-ariel.amriou
** File description:
** src.h
*/

#ifndef SRC_H_
    #define SRC_H_
    #include <SFML/Graphics.h>
    #include <SFML/System.h>
    #include <SFML/Audio.h>
    #define DISPLAY_MODE sfFullscreen
    #define MICROSEC_IN_SEC 1000000.0
    #define CLOCK_SPEED 1 * MICROSEC_IN_SEC
    #define PATH_BG1 "sprites/background1.png"
    #define PATH_BG2 "sprites/background2.png"
    #define PATH_BG3 "sprites/background3.png"
    #define INDEX_BG1 0
    #define INDEX_BG2 1
    #define INDEX_BG3 2
    #define DEFAULT_INDEX_BG 0
    #define NB_BG 3
    #define BG_WIDTH 1920
    #define BG_HEIGHT 1080
    #define BG_RATIO 16 / 9
    #define PATH_FONT "sprites/font.ttf"
    #define PATH_PLANE "sprites/plane.png"
    #define PLANE_WIDTH 20
    #define PLANE_HEIGHT 20
    #define PATH_TOWER "sprites/tower.png"
    #define TOWER_WIDTH 20
    #define TOWER_HEIGHT 60
    #define NOT_ALL_LANDED -1
    #define CLOSE_DELAY 5.0
    #define NB_SIDES 4
    #define TIME_TXT_OFFSET 7
    #define FPS_TXT_OFFSET 6
    #define PATH_HELP "src/help.txt"
    #define FRAMERATE 144
    #define DEFAULT_HITBOX sfTrue
    #define DEFAULT_SPRITE sfTrue
    #define DEFAULT_HEADER sfTrue
    #define DEFAULT_ZONE sfFalse
    #define DEFAULT_ZONE_TXT sfFalse
    #define SPLIT_CAP 7
    #define MERGE_CAP 5
    #define TXT_MARGIN 30
    #define NB_IDS_MAX 4
    #define RGB_MAX 255
    #define ZONE_THICKNESS 3
    #define NUMBER_SPLIT_MAX 8
    #define ID_CHARS 5
    #define MIN_ZONE_SIZE BG_WIDTH / NUMBER_SPLIT_MAX
    #define DEG(rad) (180 / M_PI) * rad
    #define RAD(deg) (M_PI / 180) * deg

typedef struct time_content_s {
    float sec;
    sfClock *clock;
    int t0;
    int t1;
    int delta;
} time_content_t;

typedef struct zone_s {
    sfRectangleShape *hitbox;
    sfVector2f left_top;
    sfVector2f bottom_right;
    char *id_str;
    sfText *id_txt;
    sfFont *font;
    int id;
    int number_planes;
    struct zone_s *next_zone;
} zone_t;

typedef struct game_s {
    sfRenderWindow *render_window;
    sfVector2u window_size;
    sfEvent event;
    sfBool display_hitbox;
    sfBool display_sprites;
    sfBool display_header;
    sfBool display_zones;
    sfBool display_zones_txt;
    time_content_t *timer;
    float end_time;
    zone_t **zones;
} game_t;

typedef struct background_s {
    sfTexture *sprite_texture[NB_BG];
    int index_bg;
    sfSprite *sprite;
} background_t;

typedef struct plane_s {
    sfTexture *sprite_texture;
    sfSprite *sprite;
    sfRectangleShape *hitbox;
    sfVector2f pos;
    sfVector2f end;
    sfVector2f speed;
    int delay;
    sfBool is_spawned;
    sfBool is_landed;
    sfBool protected;
    unsigned int id;
    float rotation_degrees;
    sfVector2f vectors[NB_SIDES];
    sfVector2f sides[NB_SIDES];
    sfVector2f corners[NB_SIDES];
    int zone_ids[NB_IDS_MAX];
    struct plane_s *next_plane;
} plane_t;

typedef struct tower_s {
    sfTexture *sprite_texture;
    sfSprite *sprite;
    sfCircleShape *hitbox;
    sfVector2f pos;
    float radius;
    struct tower_s *next_tower;
} tower_t;

typedef struct texts_s {
    sfText *time;
    char *time_txt;
    sfText *fps;
    char *fps_txt;
    sfFont *font;
} texts_t;

typedef struct game_sprites_s {
    plane_t *planes;
    background_t *background;
    tower_t *towers;
    texts_t *texts;
} game_sprites_t;

int are_all_numbers(char **list,
    const unsigned int start, const unsigned int end);
void sort_id(zone_t *zone);
void change_zone(zone_t *zone,
    sfVector2f top_left, sfVector2f bottom_right);
int quad_tree(game_t *game, plane_t *plane);
void merge_tree(game_t *game);
void clock_function(game_t *game, plane_t *plane);
void create_all_sfzone(zone_t *zone);
void destroy_zone(zone_t *zone);
int create_window(game_t *game);
void get_points(plane_t *plane);
int puttower(tower_t **tower, char *buff);
int putplane(plane_t **plane, char *buff);
int create_components(plane_t **plane, tower_t **tower, char *pathname);
int create_game_sprites(game_sprites_t *sprites, char *pathname);
void sort_planes(plane_t *plane, game_t *game);
void handle_planes(plane_t *plane, game_t *game, tower_t *tower);
void poll_event(game_t *game, background_t *background);
void game_loop(game_sprites_t *sprites, game_t *game);
void destroy_all(game_sprites_t *sprites, game_t *game);
void collision_planes(plane_t *planes);

#endif
