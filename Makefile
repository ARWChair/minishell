SRCS = minishell.c env_variables.c env_list.c env_list_2.c frees.c\
	builtins.c signal_handlers.c execute.c execute_utils.c builtins_utils.c heredoc.c \
	cmd_split_master.c cmd_expand.c cmd_pipe_split.c cmd_kill_quotes.c \
	cmd_save_list.c cmd_split_utils.c cmd_get_path.c helpers.c cmd_save_split_utils.c \
	cmd_get_path_utils.c cmd_kill_quotes2.c helpers2.c
OBJS = $(SRCS:.c=.o)
NAME = minishell
HDR = $(NAME).h
COMPILER = cc
RM = rm -f
CFLAGS = -Wall -Wextra -Werror -Wpedantic -g
LIBFT_PATH = ./libft/
LIBFT = $(LIBFT_PATH)libft.a

all:	$(LIBFT) $(NAME)

$(NAME):	$(OBJS) $(HDR)
	@echo "\033[1;34m- compiling executable: $@\033[0m"
	@$(COMPILER) $(CFLAGS) $(OBJS) $(LIBFT) -o $@ -lreadline
	@echo "\033[1;32m- complete!\033[0m"

%.o:	%.c
	@echo "\033[1;34m- compiling object: $<\033[0m"
	@$(COMPILER) $(CFLAGS) -o $@ -c $<

$(LIBFT):
	@make --no-print-directory all -C $(LIBFT_PATH)

clean:	
	@make --no-print-directory clean -C $(LIBFT_PATH)
	@$(RM) $(OBJS)
	@echo "\033[1;31m- objects removed\033[0m"

fclean:	clean
	@make --no-print-directory fclean -C $(LIBFT_PATH)
	@$(RM) $(NAME)
	@echo "\033[1;31m- $(NAME) removed\033[0m"

generate_test:
	valgrind --leak-check=full --show-reachable=yes --error-limit=no --gen-suppressions=all --log-file=$(NAME).log ./$(NAME)

test:
	clear; valgrind --leak-check=full --track-origins=yes --track-fds=yes --show-reachable=yes --show-leak-kinds=all --error-limit=no --suppressions=./$(NAME).supp ./$(NAME)

re:	fclean all

.PHONY:	all clean fclean re test
