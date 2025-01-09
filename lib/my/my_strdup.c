/*
** EPITECH PROJECT, 2024
** my_strdup
** File description:
** dup a string
*/

#include <stdlib.h>
#include "../../include/my.h"

char *my_strdup(char const *src)
{
    char *dup;

    dup = malloc((my_strlen(src) + 1) * sizeof(char));
    for (int i = 0; i < my_strlen(src) + 1; i++) {
        dup[i] = src[i];
    }
    return dup;
}
