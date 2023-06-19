NAME = libprintf.a
Sources = ft_printf.c ft_itohex.c len_putchar.c len_putstr.c len_itoa.c ft_pointer.c ft_u.c printf_itoa.c
Objects = $(Sources:.c=.o)

CC = cc
Cflags = -Wall -Werror -Wextra
RM = rm -f

subdir1 = libft
Cur_dir = $(shell pwd)

all: $(NAME) 
 
$(NAME): $(Objects)
	@ar -src $@ $(Objects)
	@echo $(NAME) created

$(Objects):
	@$(CC) -c $(Cflags) $(Sources)

bonus: $(bon_obj)
	@ar -src $(NAME) $(bon_obj)
	@echo bonus added to $(NAME)
	@echo $(NAME) ran with bonus

$(bon_obj):
	@$(CC) -c $(Cflags) $(bon_src)

clean:
	@rm -rf *.o
	@echo "clean done"

fclean: clean
	@rm -f $(NAME)
	@echo "fclean done"

re: fclean all
	@echo "\nRecompilation done"

seelib:
	@ar -t $(NAME)

norm: $(Sources)
	@norminette -R CheckForbiddenSourceHeader $(Sources)
	@echo all sources checked with norminette

normb: $(norm)
	@norminette -R CheckForbiddenSourceHeader $(bon_src)
	@echo all sources checked with norminette including bonus

.PHONY: all bonus clean fclean re seelib norm normb
