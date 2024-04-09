MAIN_SRCS = ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c \
		ft_strlen.c ft_memset.c ft_bzero.c ft_memcpy.c ft_memmove.c \
		ft_strlcpy.c ft_strlcat.c ft_toupper.c ft_tolower.c ft_strchr.c \
		ft_strrchr.c ft_strncmp.c ft_memchr.c ft_memcmp.c ft_strnstr.c \
		ft_atoi.c ft_calloc.c ft_strdup.c ft_substr.c ft_strjoin.c \
		ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c \
		ft_itoa.c ft_strmapi.c ft_striteri.c ft_strtrim.c ft_split.c
BONUS_SRCS = ft_lstnew.c ft_lstadd_front.c ft_lstadd_back.c ft_lstsize.c \
		ft_lstlast.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_lstmap.c
PRINTF_SRCS = ft_printf.c printf_check.c printf_c.c printf_s.c printf_d_i.c \
		printf_u.c printf_x.c printf_p.c ft_uitoa.c
GNL_SRCS = get_next_line.c
XTRA_SRCS = ft_atol.c
SRCS = $(MAIN_SRCS) $(BONUS_SRCS) $(PRINTF_SRCS) $(GNL_SRCS) $(XTRA_SRCS)
OBJS = $(SRCS:.c=.o)
NAME = libft.a
COMPILER = cc
RM = rm -f
CFLAGS = -Wall -Wextra -Werror

all:	$(NAME)

$(NAME):	$(OBJS)
	@echo "\033[3;34m- compiling $@\033[0m"
	@ar crs $@ $(OBJS)
	@echo "\033[3;32m- libft complete!\033[0m"

%.o:	%.c
	@echo "\033[3;34m- compiling libft object: $<\033[0m"
	@$(COMPILER) $(CFLAGS) -o $@ -c $<

clean:	
	@$(RM) $(OBJS)
	@echo "\033[3;31m- libft objects removed\033[0m"

fclean:	clean
	@$(RM) $(NAME)
	@echo "\033[3;31m- $(NAME) removed\033[0m"

re:	fclean all

.PHONY:	all clean fclean re