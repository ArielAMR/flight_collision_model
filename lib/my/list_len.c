/*
** EPITECH PROJECT, 2024
** B-MUL-100-PAR-1-1-myradar-ariel.amriou
** File description:
** list_len.c
*/

#include <stdio.h>

int list_len(char **list)
{
    int i = 0;

    while (list[i] != NULL)
        i++;
    return i;
}
