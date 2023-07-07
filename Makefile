# FILES
SERVER		= src/ft_server.c

CLIENT		= src/ft_client.c

LIBFT		= cd libft && make

LIB			= libft/libft.a

# SRCS

SERVER_SRC	= $(SERVER)

SERVER_OBJS	= $(SERVER_SRC:.c=.o)

CLIENT_SRC	= $(CLIENT)

CLIENT_OBJS = $(CLIENT_SRC:.c=.o)

OBJS		= $(CLIENT_OBJS) $(SERVER_OBJS)

# HEADER

INCLUDE		= -I include

# COMPILATION

CC			= clang

FLAGS		= -Werror -Wextra -Wall

SERVER_NAME	= server

CLIENT_NAME	= client

NAME		= server

all: $(NAME)

$(NAME): libft ft_server ft_client

libft:
	@$(LIBFT)

ft_server: $(SERVER_OBJS)
	@$(CC) $(FLAGS) $(SERVER_OBJS) $(LIB) -o $(SERVER_NAME)

ft_client: $(CLIENT_OBJS)
	@$(CC) $(FLAGS) $(CLIENT_OBJS) $(LIB) -o $(CLIENT_NAME)

clean:
	@rm -rf $(OBJS)
	@cd libft && make clean

fclean: clean
	@rm -rf $(SERVER_NAME) $(CLIENT_NAME)
	@cd libft && make fclean

.c.o:
	@${CC} ${FLAGS} $(INCLUDE) -c $< -o ${<:.c=.o}

re:	fclean all

.PHONY: all minitalk server client clean fclean re libft