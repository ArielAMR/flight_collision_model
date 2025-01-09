/*
** EPITECH PROJECT, 2024
** my_str_to_word_array
** File description:
** my_str_to_word_array.c
*/

#include <stdlib.h>
#include "../../include/my.h"

static int is_alphanum(char c)
{
    if (c >= 'A' && c <= 'Z') {
        return 1;
    }
    if (c >= 'a' && c <= 'z') {
        return 1;
    }
    if (c >= '0' && c <= '9') {
        return 1;
    }
    return 0;
}

static int world_count(char const *str)
{
    int i = 0;

    for (int j = 0; str[j] != '\0'; j++) {
        if (is_alphanum(str[j]) == 0 && is_alphanum(str[j + 1]) == 1) {
            i++;
        }
    }
    if (is_alphanum(str[0]) == 1) {
        i++;
    }
    return i;
}

static void word_len(char const *str, char **arr)
{
    int ch = 0;
    int word = 0;

    for (int i = 0; i < my_strlen(str) + 1; i++) {
        if (is_alphanum(str[i]) == 1) {
            ch++;
        }
        if ((is_alphanum(str[i]) == 0 || str[i] == '\0') && ch > 0) {
            arr[word] = malloc((ch + 1) * sizeof(char));
            arr[word][ch] = '\0';
            word++;
            ch = 0;
        }
    }
}

static void put_str(char const *str, char **arr)
{
    int ch = 0;
    int word = 0;

    for (int i = 0; i < my_strlen(str); i++) {
        if (is_alphanum(str[i]) == 1) {
            arr[word][ch] = str[i];
            ch++;
        }
        if (is_alphanum(str[i]) == 0 && ch > 0) {
            word++;
            ch = 0;
        }
    }
}

char **my_str_to_word_array(char const *str)
{
    int len = world_count(str) + 1;
    char **arr = malloc(len * sizeof(char *));

    arr[len - 1] = NULL;
    word_len(str, arr);
    put_str(str, arr);
    return arr;
}
