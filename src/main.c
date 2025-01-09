/*
** EPITECH PROJECT, 2024
** B-MUL-100-PAR-1-1-myhunter-ariel.amriou
** File description:
** main.c
*/

#include "src.h"
#include "my.h"
#include <unistd.h>
#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>

static void help(void)
{
    int fd = open(PATH_HELP, O_RDONLY);
    struct stat file_stats;
    char *buff = NULL;
    int size = 0;

    stat(PATH_HELP, &file_stats);
    size = file_stats.st_size;
    buff = malloc(size);
    if (fd == -1 || buff == NULL) {
        my_putstr_err("Error while openning help file.\n");
        return;
    }
    read(fd, buff, size);
    my_putstr(buff);
    free(buff);
    close(fd);
}

static int my_radar(char *pathname)
{
    game_t game = {0};
    game_sprites_t sprites = {0};

    if (create_window(&game) == 84
        || create_game_sprites(&sprites, pathname) == 84)
        return 84;
    game_loop(&sprites, &game);
    return 0;
}

int main(int argc, char **argv)
{
    if (argc != 2) {
        my_putstr_err("./my_radar: bad arguments: ");
        my_put_nbr_err(argc);
        my_putstr_err(" given but 2 is required\nretry with -h\n");
        return 84;
    } else if (argv[1][0] == '-' && argv[1][1] == 'h' && argv[1][2] == '\0') {
        help();
        return 0;
    }
    return my_radar(argv[1]);
}
