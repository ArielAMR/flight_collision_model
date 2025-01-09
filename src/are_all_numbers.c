/*
** EPITECH PROJECT, 2024
** B-MUL-100-PAR-1-1-myradar-ariel.amriou
** File description:
** are_all_numbers.c
*/

#include "my.h"
#include <stdlib.h>

int are_all_numbers(char **list,
    const unsigned int start, const unsigned int end)
{
    for (size_t i = start; i <= end; i++)
        if (!my_is_number(list[i]))
            return 84;
    return 0;
}
