##
## EPITECH PROJECT, 2018
## PSU_myirc_2017
## File description:
## main.c
##

SRC_SERVER	=	src/common/free_array.c				\
				src/common/is_positive_integer.c	\
				src/common/len_array.c				\
				src/common/poll_cond.c				\
				src/common/poll_interact.c			\
				src/common/poll_wait.c				\
				src/common/split_str.c				\
				src/common/str_tolower.c			\
				src/server/data_sendf/data_sendf.c	\
				src/server/data_sendf/place_char.c	\
				src/server/data_sendf/place_int.c	\
				src/server/data_sendf/place_str.c	\
				src/server/data_sendf/place_unsigned_int.c	\
				src/server/fnt/nick.c				\
				src/server/fnt/user.c				\
				src/server/accept_client.c			\
				src/server/client.c					\
				src/server/create_server.c			\
				src/server/data_send.c				\
				src/server/exec_cmd.c				\
				src/server/main.c					\
				src/server/parse_cmd.c				\
				src/server/read_all_client.c		\
				src/server/sock_io.c				\
				src/server/update_write_poll.c		\
				src/server/write_all_client.c

SRC_CLIENT	=	src/common/is_positive_integer.c	\
				src/common/poll_cond.c				\
				src/common/poll_interact.c			\
				src/common/poll_wait.c				\
				src/common/malloc.c					\
				src/client/core/cmd/action.c		\
				src/client/core/cmd/server.c		\
				src/client/core/cmd/nick.c			\
				src/client/core/cmd/list.c			\
				src/client/core/cmd/join.c			\
				src/client/core/cmd/part.c			\
				src/client/core/cmd/users.c			\
				src/client/core/cmd/names.c			\
				src/client/core/cmd/msg.c			\
				src/client/core/cmd/accept_file.c	\
				src/client/core/cmd/broadcast.c		\
				src/client/core/sess/init.c			\
				src/client/core/sess/event.c		\
				src/client/core/sess/action.c		\
				src/client/core/logger/init.c		\
				src/client/core/logger/logger.c		\
				src/client/ui/event.c				\
				src/client/ui/init.c				\
				src/client/ui/update.c				\
				src/client/ui/wchat.c				\
				src/client/ui/wchan.c				\
				src/client/ui/winfo.c				\
				src/client/ui/wlogs.c				\
				src/client/ui/window.c				\
				src/client/sighandler.c				\
				src/client/main.c

OBJ_SERVER	=	$(SRC_SERVER:.c=.o)

OBJ_CLIENT	=	$(SRC_CLIENT:.c=.o)

NAME_SERVER	=	server

NAME_CLIENT	=	client

CFLAGS		=	-Iinclude -W -Wall -Wextra -g

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