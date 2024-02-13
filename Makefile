NAME = minishell

COMPILER = cc

FLAGS = -Wall -Wextra -Werror -g #-fsanitize=address
OTHERFLAGS = -lreadline

FILES = main.c \
		utilities/ft_putstr_fd.c \
		utilities/ft_strncmp.c \
		utilities/ft_strcmp.c \
		utilities/ft_strdup.c \
		utilities/ft_strndup.c \
		utilities/ft_strlen.c \
		utilities/ft_strjoin.c \
		utilities/ft_strchr.c \
		utilities/ft_substr.c \
		utilities/ft_isdigit.c \
		utilities/ft_itoa.c \
		utilities/ft_strlcpy.c \
		utilities/ft_split.c \
		structure_tools.c \
		tokenizing.c \
		tokenizing_2.c \
		tokenizing_3.c \
		parsing.c \
		parsing_tools.c \
		get_env.c \
		syntax_error.c \
		syntax_error1.c \
		syntax_error2.c \
		syntax_error3.c \
		expanding1.c \
		expanding2.c \
		expanding3.c \
		token_helper.c \
		check_expand.c \
		execution.c \
		structure_helper.c \
		printdata.c

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
