NAME = minishell

COMPILER = cc

FLAGS = -Wall -Wextra -Werror
OTHERFLAGS = -lreadline  -L  /Users/mel-jira/homebrew/opt/readline/lib

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
		utilities/ft_lstsize.c \
		utilities/ft_putchar_fd.c \
		utilities/ft_strcat.c \
		utilities/ft_strcpy.c \
		utilities/ft_strrcmp.c \
		utilities/ft_atoi.c \
		execution/builtins/ft_cd.c \
		execution/builtins/ft_echo.c \
		execution/builtins/ft_env.c \
		execution/builtins/ft_export.c \
		execution/builtins/ft_exit.c \
		execution/builtins/ft_exit1.c \
		execution/builtins/ft_pwd.c \
		execution/builtins/ft_unset.c \
		execution/add_to_list.c \
		execution/check_bult.c \
		execution/find_path.c \
		execution/list_to_tab.c \
		execution/pars_args.c \
		execution/red_help1.c \
		execution/red_help2.c \
		execution/red_help3.c \
		execution/red_help4.c \
		execution/red_help5.c \
		execution/redirections.c \
		structure_tools.c \
		structure_tools2.c \
		tokenizing.c \
		tokenizing_2.c \
		tokenizing_3.c \
		tokenizing_4.c \
		parsing.c \
		parsing2.c \
		parsing3.c \
		parsing_tools.c \
		get_env.c \
		get_env_help.c \
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
		structure_helper2.c \
		signals.c \
		printdata.c \
		garbg_clctr.c

OBJ = $(FILES:.c=.o)

all: $(NAME)

$(NAME) : $(OBJ)
	$(COMPILER) $(FLAGS) $(OTHERFLAGS) $(OBJ) -o $(NAME)

%.o: %.c minishell.h
	$(COMPILER) $(FLAGS) -I /Users/mel-jira/homebrew/opt/readline/include -c $< -o $@

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all
