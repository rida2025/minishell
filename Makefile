NAME = minishell

COMPILER = cc

FLAGS = -Wall -Wextra -Werror #-g -fsanitize=address
OTHERFLAGS = -lreadline

FILES = main.c \
		ft_strncmp.c \
		ft_strcmp.c \
		ft_strdup.c \
		ft_strndup.c \
		insert_data.c \
		get_words.c \
		structure_tools.c \
		ft_strlen.c \
		parsing.c \
		ft_strjoin.c \
		ft_strchr.c \
		get_env.c \
		ft_substr.c \
		reda_hammer.c \
		check_syntax_error.c

OBJ = $(FILES:.c=.o)

all: $(NAME)

$(NAME) : $(OBJ)
	$(COMPILER) $(FLAGS) $(OTHERFLAGS) $(OBJ) -o $(NAME)

%.o: %.c minishell.h
	$(COMPILER) $(FLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all
