/*
** EPITECH PROJECT, 2024
** my_intlen
** File description:
** count the number of char in an int
*/

int my_intlen(int i)
{
    int count = 1;

    if (i == -2147483648)
        return 20;
    if (i < 0) {
        i *= -1;
        count++;
    }
    while (i > 9){
        i = i / 10;
        count++;
    }
    return count;
}
