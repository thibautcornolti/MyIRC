##
## EPITECH PROJECT, 2018
## PSU_myirc_2017
## File description:
## main.c
##

SRC_SERVER	=	src/common/sendf/asendf.c					\
				src/common/sendf/data_sendf.c				\
				src/common/sendf/place_char.c				\
				src/common/sendf/place_int.c				\
				src/common/sendf/place_str.c				\
				src/common/sendf/place_unsigned_int.c		\
				src/common/free_array.c						\
				src/common/is_positive_integer.c			\
				src/common/len_array.c						\
				src/common/poll_cond.c						\
				src/common/poll_interact.c					\
				src/common/poll_wait.c						\
				src/common/split_cmd.c						\
				src/common/split_str.c						\
				src/common/str_tolower.c					\
				src/server/data_sendf/data_sendf.c			\
				src/server/fnt/join.c						\
				src/server/fnt/list.c						\
				src/server/fnt/names.c						\
				src/server/fnt/nick.c						\
				src/server/fnt/part.c						\
				src/server/fnt/privmsg.c					\
				src/server/fnt/quit.c						\
				src/server/fnt/user.c						\
				src/server/fnt/users.c						\
				src/server/accept_client.c					\
				src/server/broadcast_channel.c				\
				src/server/broadcast_nick_change.c			\
				src/server/channel.c						\
				src/server/channel_exist.c					\
				src/server/client.c							\
				src/server/close_empty_chan.c				\
				src/server/create_server.c					\
				src/server/data_send.c						\
				src/server/exec_cmd.c						\
				src/server/free_channel.c					\
				src/server/free_data_msg.c					\
				src/server/get_user_by_chan.c				\
				src/server/main.c							\
				src/server/parse_cmd.c						\
				src/server/read_all_client.c				\
				src/server/sock_io.c						\
				src/server/update_write_poll.c				\
				src/server/write_all_client.c

SRC_CLIENT	=	src/common/sendf/asendf.c					\
				src/common/sendf/data_sendf.c				\
				src/common/sendf/place_char.c				\
				src/common/sendf/place_int.c				\
				src/common/sendf/place_str.c				\
				src/common/sendf/place_unsigned_int.c		\
				src/common/free_array.c						\
				src/common/is_positive_integer.c			\
				src/common/poll_cond.c						\
				src/common/poll_interact.c					\
				src/common/poll_wait.c						\
				src/common/len_array.c						\
				src/common/split_cmd.c						\
				src/common/split_str.c						\
				src/common/malloc.c							\
				src/common/str_tolower.c					\
				src/client/core/channel/add_chan.c			\
				src/client/core/channel/free_chan.c			\
				src/client/core/channel/push_log.c			\
				src/client/core/channel/rm_chan.c			\
				src/client/core/cmd/action.c				\
				src/client/core/cmd/server.c				\
				src/client/core/cmd/server_tools.c			\
				src/client/core/cmd/nick.c					\
				src/client/core/cmd/list.c					\
				src/client/core/cmd/join.c					\
				src/client/core/cmd/part.c					\
				src/client/core/cmd/send_file.c				\
				src/client/core/cmd/users.c					\
				src/client/core/cmd/names.c					\
				src/client/core/cmd/msg.c					\
				src/client/core/cmd/accept_file.c			\
				src/client/core/cmd/broadcast.c				\
				src/client/core/cmd/ip_form_sock.c			\
				src/client/core/send_file/convert_ip.c		\
				src/client/core/send_file/create_serv.c		\
				src/client/core/send_file/handle_send_serv.c\
				src/client/core/send_file/send_file.c		\
				src/client/core/send_file/swap_endian.c		\
				src/client/core/sess/init.c					\
				src/client/core/sess/event.c				\
				src/client/core/sess/action.c				\
				src/client/core/logger/init.c				\
				src/client/core/logger/logger.c				\
				src/client/core/resp/get_nickname.c			\
				src/client/core/resp/join.c					\
				src/client/core/resp/list.c					\
				src/client/core/resp/names.c				\
				src/client/core/resp/no_action.c			\
				src/client/core/resp/part.c					\
				src/client/core/resp/pretty_size.c			\
				src/client/core/resp/privmsg.c				\
				src/client/core/resp/nick_used.c			\
				src/client/core/commander/init.c			\
				src/client/core/commander/commander.c		\
				src/client/core/get_file/create_client.c	\
				src/client/core/get_file/handle_get_file.c	\
				src/client/core/get_file/init_get_file.c	\
				src/client/core/handle_transfer.c			\
				src/client/ui/create_ui.c					\
				src/client/ui/event.c						\
				src/client/ui/init.c						\
				src/client/ui/update.c						\
				src/client/ui/wchat.c						\
				src/client/ui/wchan.c						\
				src/client/ui/winfo.c						\
				src/client/ui/wlogs.c						\
				src/client/ui/window.c						\
				src/client/sighandler.c						\
				src/client/main.c

OBJ_SERVER	=	$(SRC_SERVER:.c=.o)

OBJ_CLIENT	=	$(SRC_CLIENT:.c=.o)

NAME_SERVER	=	server

NAME_CLIENT	=	client

CFLAGS		=	-Iinclude -W -Wall -Wextra -g -D _GNU_SOURCE

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