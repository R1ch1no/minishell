
NAME = libprintf.a
Sources = ft_printf.c \
		ft_itohex.c \
		len_putchar.c \
		len_putstr.c \
		len_itoa.c \
		ft_pointer.c \
		ft_u.c \
		printf_itoa.c

Objects = $(Sources:.c=.o)

CC = cc
Cflags = -Wall -Werror -Wextra

.PHONY: all bonus clean fclean re seelib norm normb
all: $(NAME) 
 
$(NAME): $(Objects)
	@ar -src $@ $(Objects)
	@echo $(NAME) created

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -f $(Objects)
	@echo "clean done"

fclean: 
	@rm -f $(Objects)
	@rm -f $(NAME)
	@echo "fclean done"

re: fclean all
	@echo "\nRecompilation done"

seelib:
	@ar -t $(NAME)

norm: $(Sources)
	@norminette -R CheckForbiddenSourceHeader $(Sources)
	@echo all sources checked with norminette
