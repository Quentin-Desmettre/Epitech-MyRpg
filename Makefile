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
	src/main.c                                                 \
	src/settings/apply.c                                       \
	src/settings/checkbox.c                                    \
	src/settings/destroy.c                                     \
	src/settings/load.c                                        \
	src/settings/move_settings.c                               \
	src/settings/rendering_evt.c                               \
	src/settings/save.c                                        \
	src/settings/scale_settings.c                              \
	src/settings/set_evt.c                                     \
	src/settings/set_evt_manager.c                             \
	src/settings/settings.c                                    \
	src/settings/sound_evt.c                                   \
	src/settings/visu_updates.c

OBJ = $(SRC:.c=.o)

NAME = myrpg

CFLAGS = -Wall -Wextra -I ./include/ -I lib/my/include/

LDFLAGS += -L lib/my/ -lmy -lcsfml-graphics -lcsfml-window \
	-lcsfml-system -lcsfml-audio -lm

all: $(NAME)

$(NAME):   $(OBJ)
	make -s -C lib/my/
	gcc -o $(NAME) $(FLAGS) $(OBJ) $(LDFLAGS)

clean:
	rm -f $(OBJ)
	make -s -C lib/my clean

fclean:    clean
	rm -f $(NAME)
	make -s -C lib/my fclean

re:        fclean all
