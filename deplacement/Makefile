##
## EPITECH PROJECT, 2019
## Makefile
## File description:
## Makefile
##

SRC	=	main.c \
		move_player.c \
		anime_move.c \

OBJ	=	$(SRC:.c=.o)

NAME	=	rpg

all:	$(NAME)

$(NAME):	$(OBJ)
	make -C "lib/my/"
	gcc -o $(NAME) $(SRC) -L "lib/my/" -lmy -lcsfml-graphics -lcsfml-window -lcsfml-system -lcsfml-audio

clean:
	make clean -C "lib/my/"
	rm -f $(OBJ)

fclean:	clean
	make fclean -C "lib/my/"
	rm -f $(NAME)

re:	fclean all