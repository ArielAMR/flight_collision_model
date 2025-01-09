/*
** EPITECH PROJECT, 2024
** my_putstr
** File description:
** print the string
*/

#include "../../include/my.h"
#include <unistd.h>

int my_putstr(char const *str)
{
    int len = my_strlen(str);

    write(1, str, len);
    return len;
}

int my_putstr_err(char const *str)
{
    int len = my_strlen(str);

    write(2, str, len);
    return len;
}
