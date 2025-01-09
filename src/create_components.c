/*
** EPITECH PROJECT, 2024
** B-MUL-100-PAR-1-1-myradar-ariel.amriou
** File description:
** create_components.c
*/

#include "my.h"
#include "src.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

int create_components(plane_t **plane, tower_t **tower, char *pathname)
{
    FILE *fd = fopen(pathname, "r");
    size_t size = 0;
    char *buff = NULL;

    if (fd == NULL)
        return 84;
    while (getline(&buff, &size, fd) != -1) {
        if (buff[0] == '/')
            continue;
        if (buff[0] == 'A' && buff[1] == ' ' && putplane(plane, buff) != 84)
            continue;
        if (buff[0] == 'T' && buff[1] == ' ' && puttower(tower, buff) != 84)
            continue;
        return 84;
    }
    free(buff);
    fclose(fd);
    return 0;
}
