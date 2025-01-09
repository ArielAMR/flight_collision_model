/*
** EPITECH PROJECT, 2024
** my_getnbr
** File description:
** la last des last
*/

#include "../../include/my.h"
#include <stdlib.h>

static int is_neg(char const *str)
{
    int neg = 1;
    int len = my_strlen(str);

    for (int i = 0; i < len; i++) {
        if (str[i] != '-' && str[i] != '+' && str[i] != ' ') {
            break;
        }
        if (str[i] == ' ' || str[i] == '+') {
            continue;
        }
        neg *= -1;
    }
    if (neg == 1){
        return 1;
    } else {
        return 0;
    }
}

static int get_first(char const *str)
{
    int len = my_strlen(str);

    for (int i = 0; i < len + 1; i++){
        if (str[i] >= '0' && str[i] <= '9')
            return i;
        if (str[i] != ' ' && str[i] != '+' && str[i] != '-'
            && (str[i] < '0' || str[i] > '9'))
            return 127;
    }
    return 0;
}

static int get_last(char const *str)
{
    int j = get_first(str);
    int i = j;
    int len = my_strlen(str);

    if (j == 127) {
        return 127;
    }
    for (; i < len + 1; i++) {
        if (str[i] > '9' || str[i] < '0') {
            return (i - 1);
        }
    }
    return 0;
}

int return_str(char const *str)
{
    int nb = 0;
    int pwr = 1;
    int i = get_first(str);
    int j = get_last(str);

    if (str[i] == '\0' && i == j){
        return 0;
    }
    for (int k = j; k >= i; k--) {
        nb += pwr * (str[k] - '0');
        pwr *= 10;
    }
    return nb;
}

int is_too_big(char const *str, int i, char *extr, int k)
{
    int j = get_last(str);

    if (str[i] == '\0' || i > j)
        return 0;
    if (str[i] > extr[k])
        return 1;
    if (str[i] < extr[k])
        return 0;
    is_too_big(str, i + 1, extr, k + 1);
    return 0;
}

int my_getnbr(char const *str)
{
    int nb = return_str(str);
    int i = get_first(str);
    int j = get_last(str);
    int len = j - i + 1;

    if (i == 127)
        return 0;
    if (is_neg(str) == 0 &&
        ((len == 10 && is_too_big(str, i, "2147483648", 0) == 1)
    || len > 10))
        return 0;
    if (is_neg(str) == 1 &&
        ((len == 10 && is_too_big(str, i, "2147483647", 0) == 1)
    || len > 10))
        return 0;
    if (is_neg(str) == 0)
        nb *= -1;
    return nb;
}
