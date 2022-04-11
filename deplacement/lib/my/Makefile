##
## EPITECH PROJECT, 2019
## Makefile
## File description:
## Makefile for libmy
##

SRC	=	my_putchar.c \
		my_putnbr.c \
		my_putstr.c \
		no_ascii.c \
		my_atoi.c \
		first_line_int.c \
		first_line_len.c \
		my_strlen.c \
		unsigned_putnbr.c \
		decimal_to_octal.c \
		decimal_to_hex.c \
		decimal_to_bi.c \
		decimal_to_hex_maj.c \
		display_sign.c \
		my_strlen.c \
		my_printf.c \
		display_array.c \
		my_strcmp.c \
		my_strcat.c \
		button.c

OBJ	=	$(SRC:.c=.o)

NAME = libmy.a

all:	$(NAME)

$(NAME):	$(OBJ)
	ar rc $(NAME) $(OBJ)

clean:
	rm -f $(OBJ)

fclean:	clean
	rm -f $(NAME)

re:	fclean all