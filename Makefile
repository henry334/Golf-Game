##
## PROJECT, 2024
## Assignement1
## File description:
## Makefile
##

CC	=	g++

LIB		=	./lib/my/geodraw.cpp

SRC_CORE	=	main.c \
				./src/game.c \
				./src/player.c \
				./src/free.c \
				./src/display.c

OBJ_CORE	=	$(SRC_CORE:.c=.o)

CFLAGS	=	-std=c++20 -Wall -Wextra -Werror -g3

CPPFLAGS	=	-I./ -I./includes/

NAME	=	assignement

NAMELIB =	libmy.a

all:	libmy	core


core:	$(OBJ_CORE)
	$(CC) -g3 -o $(NAME) $(OBJ_CORE) $(CFLAGS) $(CPPFLAGS) -L ./lib/my -lmy
	make clean
	./$(NAME)

libmy:
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $(LIB)
	@ar rc ./lib/my/$(NAMELIB) *.o
	@rm -f lib/my/*.o
	@echo "CREATED LIB: OK"

clean:
	$(RM) $(OBJ_CORE)
	$(RM) *.o

fclean: clean
	$(RM) $(NAME)

re:
	$(MAKE) fclean
	$(MAKE) all

.PHONY:	all clean fclean re core