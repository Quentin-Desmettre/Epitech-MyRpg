##
## EPITECH PROJECT, 2021
## Makefile
## File description:
## Makefile
##

SRC = \
	src/button/button.c                                        \
	src/button/change_button.c                                 \
	src/button/get_button_ev.c                                 \
	src/sprite/init_sprite.c                                   \
	src/sprite/sprite_modif.c                                  \
	src/globals/fonts.c                                        \
	src/globals/texture.c                                      \
	src/main.c

OBJ = $(SRC:.c=.o)

NAME = myrpg

CFLAGS = -Wall -Wextra -I ./include/

LDFLAGS += -L lib/my/ -lmy -lcsfml-graphics -lcsfml-window \
	-lcsfml-system -lcsfml-audio

all: $(NAME)

$(NAME):   $(OBJ)
	make -s -C lib/my/
	gcc -o $(NAME) $(FLAGS) $(OBJ) $(LDFLAGS)

clean:
	rm -f $(OBJ)

fclean:    clean
	rm -f $(NAME)

re:        fclean all
