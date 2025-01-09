/*
** EPITECH PROJECT, 2024
** B-MUL-100-PAR-1-1-myradar-ariel.amriou
** File description:
** sort_id.c
*/

#include "src.h"

static void id_to_str(char *str, int id)
{
    if (id < 100) {
        str[0] = ' ';
        str[1] = (id / 10) + '0';
        str[2] = (id % 10) + '0';
        str[3] = '\0';
        str[4] = '\0';
        return;
    }
    if (id > 999)
        id = 999;
    str[0] = ' ';
    str[1] = (id / 100) + '0';
    str[2] = (id / 10 % 10) + '0';
    str[3] = (id % 10) + '0';
    str[4] = '\0';
}

void sort_id(zone_t *zone)
{
    int id = 1;

    while (zone != NULL) {
        zone->id = id;
        id_to_str(zone->id_str, id);
        sfText_setString(zone->id_txt, zone->id_str);
        id++;
        zone = zone->next_zone;
    }
}
