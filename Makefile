##
## EPITECH PROJECT, 2018
## PSU_myirc_2017
## File description:
## main.c
##

SRC_SERVER	=	src/common/is_positive_integer.c	\
				src/common/poll_cond.c				\
				src/common/poll_interact.c			\
				src/common/poll_wait.c				\
				src/server/accept_client.c			\
				src/server/client.c					\
				src/server/create_server.c			\
				src/server/main.c

OBJ_SERVER	=	$(SRC_SERVER:.c=.o)

NAME_SERVER	=	server

CFLAGS	=	-Iinclude

all:	$(NAME_SERVER)

$(NAME_SERVER):	$(OBJ_SERVER)
			gcc -o $(NAME_SERVER) $(OBJ_SERVER)

clean:
			rm -rf $(OBJ_SERVER)

fclean: clean
		rm -rf $(NAME_SERVER)

re:		fclean all

.PHONY:	all clean fclean re