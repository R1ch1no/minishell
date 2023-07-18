
NAME = libft.a

Sources = ft_atoi.c ft_bzero.c ft_tolower.c ft_toupper.c \
	  ft_isalnum.c ft_isalpha.c ft_isascii.c ft_isdigit.c ft_isprint.c \
	  ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memmove.c ft_memset.c \
	  ft_strlen.c ft_strchr.c  ft_strlcat.c ft_strlcpy.c ft_strncmp.c ft_strnstr.c ft_strrchr.c \
	  ft_strdup.c ft_calloc.c \
	  ft_strjoin.c ft_strtrim.c ft_substr.c ft_split.c ft_itoa.c ft_strmapi.c ft_striteri.c \
	  ft_putchar_fd.c ft_putstr_fd.c ft_putnbr_fd.c ft_putendl_fd.c \
	  get_next_line_utils_bonus.c get_next_line_bonus.c


bon_src = ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c 

PRINTF_DIR = printf

PRINTF_SOURCES =	ft_itohex.c \
					ft_pointer.c \
					ft_printf.c \
					ft_u.c \
					len_itoa.c \
					len_putchar.c \
					len_putstr.c \
					printf_itoa.c

PRINTF_SRCS	= $(addprefix $(PRINTF_DIR)/, $(PRINTF_SOURCES))
PRINTF_OBJS = $(PRINTF_SRCS:.c=.o)

Objects = $(Sources:.c=.o)
bon_obj = $(bon_src:.c=.o)

CC = cc
Cflags = -Wall -Werror -Wextra

.PHONY: all bonus clean fclean re seelib norm normb
all: $(NAME)

$(NAME): $(Objects)
	@$(MAKE) -C printf
	@ar -src $@ $(Objects) $(PRINTF_OBJS)
	@echo $(NAME) created
	
%.o: %.c
	@$(CC) -c $(Cflags) $< -o $@

#$(Objects):
#	$(CC) -c $(Cflags) $(Sources)

clean:
	@rm -f $(Objects)
	@$(MAKE) -C $(PRINTF_DIR) clean
	@echo "clean done"


fclean:
	@rm -f $(Objects)
	@rm -f $(NAME)
	@$(MAKE) -C $(PRINTF_DIR) fclean
	@echo "fclean done"


re: fclean all
	@echo "recompilation done"


bonus: $(bon_obj) all
	@ar -src $(NAME) $(bon_obj)
	@echo bonus added to $(NAME)
	@echo $(NAME) ran with bonus

$(bon_obj):
	@$(CC) -c $(Cflags) $(bon_src)


seelib:
	@ar -t $(NAME)

norm: $(Sources)
	@norminette -R CheckForbiddenSourceHeader $(Sources)
	@echo all sources checked with norminette


normb: norm
	@norminette -R CheckForbiddenSourceHeader $(bon_src)
	@echo all functions checked with norminette including bonus

