##
## EPITECH PROJECT, 2024
## makefile
## File description:
## root makefile
##

SRC =	my_pow.c			 		\
		my_sqrt.c 				 	\
		my_find_prime_sup.c 		\
		my_getnbr.c 				\
		my_intlen.c 				\
		my_isneg.c 					\
		my_is_prime.c 				\
		my_putchar.c 				\
		my_putchar_error.c 			\
		my_put_nbr.c 				\
		my_putstr.c 				\
		my_strcat.c 				\
		my_strcmp.c 				\
		my_strcpy.c 				\
		my_str_error.c 				\
		my_str_isalpha.c			\
		my_str_islower.c			\
		my_str_isnum.c				\
		my_str_isprintable.c		\
		my_str_isupper.c			\
		my_strlen.c					\
		my_strlowcase.c				\
		my_strncat.c				\
		my_strstr.c					\
		my_str_to_word_array.c		\
		my_strupcase.c				\
		my_swap.c					\
		my_is_number.c				\
		free_list.c					\
		list_len.c					\
		my_strdup.c

OBJ = $(SRC:.c=.o)

CFLAGS += -Wall -Wextra

CPPFLAGS += -iquote include

all:	crlib

crlib:	$(OBJ)
	ar rc libmy.a $(OBJ)
	mv libmy.a ../

clean:
	$(RM) $(OBJ)

.PHONY:	all	crlib	clean
