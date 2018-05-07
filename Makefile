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
				src/server/create_server.c			\
				src/server/main.c

SRC_CLIENT	=	src/common/is_positive_integer.c	\
				src/common/poll_cond.c				\
				src/common/poll_interact.c			\
				src/common/poll_wait.c				\
				src/client/ui/ui.c					\
				src/client/main.c

OBJ_SERVER	=	$(SRC_SERVER:.c=.o)

OBJ_CLIENT	=	$(SRC_CLIENT:.c=.o)

NAME_SERVER	=	server

NAME_CLIENT	=	client

CFLAGS		=	-Iinclude

LDFLAGS		=	-lncurses


all:			$(NAME_SERVER) $(NAME_CLIENT)

$(NAME_SERVER):	$(OBJ_SERVER)
				gcc -o $(NAME_SERVER) $(OBJ_SERVER)

$(NAME_CLIENT):	$(OBJ_CLIENT)
				gcc -o $(NAME_CLIENT) $(OBJ_CLIENT) $(LDFLAGS)

clean:
				rm -rf $(OBJ_SERVER)
				rm -rf $(OBJ_CLIENT)

fclean: 		clean
				rm -rf $(NAME_SERVER)
				rm -rf $(NAME_CLIENT)

re:				fclean all

.PHONY:			all clean fclean re