/*
** EPITECH PROJECT, 2024
** my_str_error.c
** File description:
** my str error
*/

#include "../../include/my.h"

void my_str_error(char *str)
{
    for (int i = 0; i < my_strlen(str); i++)
        my_putchar_error(str[i]);
}
