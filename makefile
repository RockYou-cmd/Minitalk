CC = gcc
CFLAGS = -Wall -Wextra -Werror

.PHONY: all bonus libft clean fclean re

all: server client

server: server.c libft
	$(CC) $(CFLAGS) server.c libft/libft.a -o server

client: client.c libft
	$(CC) $(FLAGS) client.c libft/libft.a -o client

bonus: libft bonus/client_bonus.c bonus/server_bonus.c
	$(CC) $(CFLAGS) bonus/server_bonus.c libft/libft.a -o bonus/server_bonus
	$(CC) $(CFLAGS) bonus/client_bonus.c libft/libft.a -o bonus/client_bonus

libft:
	make -C libft

clean:
	make -C libft clean
	
fclean: clean
	rm -f server client libft/libft.a ./bonus/server_bonus ./bonus/client_bonus

re: fclean all
