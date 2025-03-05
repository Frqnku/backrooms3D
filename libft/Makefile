NAME = libft.a
SRCS = ft_strlen.c ft_strncmp.c ft_atoi.c ft_split.c ft_itoa.c ft_free_split.c \
	ft_putendl_fd.c ft_count_words.c ft_strrchr.c ft_substr.c ft_strnstr.c ft_strchr.c \
	get_next_line.c ft_strjoin.c ft_calloc.c get_char_index.c ft_strdup.c ft_is_whitespace.c \
	ft_get_tab_size.c ft_strtrim.c
OBJS = $(SRCS:.c=.o)
CFLAGS = -Werror -Wall -Wextra

all: $(NAME)

$(NAME): $(OBJS)
	@ar rcs $(NAME) $(OBJS)

%.o: %.c
	@gcc $(CFLAGS) -I . -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re