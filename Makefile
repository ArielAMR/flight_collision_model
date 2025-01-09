##
## EPITECH PROJECT, 2024
## B-MUL-100-PAR-1-1-myhunter-ariel.amriou
## File description:
## Makefile
##

SRC =	src/clock_function.c	\
		src/sort_id.c			\
		src/change_zone.c		\
		src/create_all_sfzone.c	\
		src/merge_tree.c		\
		src/quad_tree.c			\
		src/create_window.c		\
		src/create_sprite.c		\
		src/poll_event.c		\
		src/game_loop.c			\
		src/destroy_all.c		\
		src/sort_planes.c		\
		src/handle_planes.c		\
		src/collision_planes.c	\
		src/get_points.c		\
		src/are_all_numbers.c	\
		src/puttower.c			\
		src/putplane.c			\
		src/create_components.c	\
		src/main.c

CC ?= gcc

OBJ = $(SRC:.c=.o)

CFLAGS += -Wall -Wextra

CPPFLAGS += -iquote include

NAME = flight_collision_model

all: crlib	cmp

crlib:
	make -C lib/my/

cmp:	$(OBJ)
	gcc -o $(NAME) $(CPPFLAGS) $(CFLAGS) $(OBJ)		\
	-Llib -lmy -lcsfml-graphics -lcsfml-system		\
	-lcsfml-audio -lcsfml-window -lm

clean:
	$(RM) $(OBJ)
	make -C lib/my/ clean

fclean:	clean
	$(RM) $(NAME)
	$(RM) lib/libmy.a

re: fclean all

.PHONY: all re clean fclean cmp crlib
