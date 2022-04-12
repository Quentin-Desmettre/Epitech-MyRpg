##
## EPITECH PROJECT, 2021
## Makefile
## File description:
## Makefile
##

SRC = \
	src/button/button.c							\
	src/button/change_button.c					\
	src/button/get_button_ev.c					\
	src/button/build_button.c					\
	src/button/setters.c						\
	src/button/setters_next.c					\
	src/sprite/init_sprite.c					\
	src/sprite/sprite_modif.c					\
	src/globals/fonts.c							\
	src/globals/texture.c						\
	src/main.c									\
	src/settings/apply.c						\
	src/settings/checkbox.c						\
	src/settings/destroy.c						\
	src/settings/load.c							\
	src/settings/move_settings.c				\
	src/settings/rendering_evt.c				\
	src/settings/save.c							\
	src/settings/scale_settings.c				\
	src/settings/set_evt.c						\
	src/settings/set_evt_manager.c				\
	src/settings/settings.c						\
	src/settings/sound_evt.c					\
	src/settings/visu_updates.c					\
	src/main_menu/create.c						\
	src/main_menu/events.c						\
	src/global_win/init_window.c				\
	src/global_win/rescale_all.c				\
	src/global_win/transition.c					\
	src/clock/my_clock.c						\
	src/clock/time.c							\
	src/game/init_game.c						\
	src/builders/npc.c							\
	src/builders/npc_setters.c					\
	src/builders/npc_setters2.c					\
	src/builders/npc_setters3.c					\
	src/builders/level.c						\
	src/builders/level_setters.c				\
	src/room/room.c								\
	src/room/generator.c						\
	src/room/valid.c							\
	src/light/set.c								\
	src/light/main_l.c							\
	src/light/utils.c							\
	src/light/utils_light.c						\
	src/light/my_memset.c						\
	src/light/draw_room.c						\
	src/light/angles.c						\


OBJ = $(SRC:.c=.o)

NAME = my_rpg

CFLAGS = -Wall -Wextra -I ./include/ -I lib/my/include/ -g

LDFLAGS += -L lib/my/ -lmy -lcsfml-graphics -lcsfml-window \
	-lcsfml-system -lcsfml-audio -lm

all: $(NAME)

$(NAME):   $(OBJ)
	make -s -C lib/my/
	gcc -o $(NAME) $(FLAGS) $(OBJ) $(LDFLAGS)

clean:
	find . -name "*.o" -delete
	rm -f $(OBJ)

fclean:    clean
	rm -f $(NAME)
	rm -f *.c~
	rm -f *.out
	rm -f vgcore*
	rm -f *.gcda
	rm -f *.gcno
	rm -f unit_tests*

re:        fclean all

run: all
	./$(NAME)

lib_fclean:
	cd lib/my/ && make fclean

push_fclean: fclean
	cd lib/my/ && make fclean

re:	fclean all

valgrind: all
	valgrind --track-origins=yes --leak-check=full \
	--show-leak-kinds=definite,indirect ./$(NAME)

tests_run: exec_lib
	gcc -o unit_tests $(SRC) tests/*.c -Llib/ -lmy --coverage -lcriterion
	./unit_tests
	gcovr --exclude tests
	gcovr -b --exclude tests
