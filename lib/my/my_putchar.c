/*
** EPITECH PROJECT, 2024
** my_putchar
** File description:
** print c
*/

#include <unistd.h>

void my_putchar_err(char c)
{
    write(2, &c, 1);
}

void my_putchar(char c)
{
    write(1, &c, 1);
}
