/*
** EPITECH PROJECT, 2024
** B-MUL-100-PAR-1-1-myradar-ariel.amriou
** File description:
** free_list.c
*/

#include <stdlib.h>

void free_list(char **list)
{
    for (int i = 0; list[i] != NULL; i++)
        free(list[i]);
    free(list);
}
