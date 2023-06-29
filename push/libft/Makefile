# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: qtran <qtran@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/26 16:53:14 by qtran             #+#    #+#              #
#    Updated: 2023/06/19 19:20:13 by qtran            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

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

PRINTF_SRC = $(PRINTF_DIR)/ft_itohex.c \
				$(PRINTF_DIR)/ft_pointer.c \
				$(PRINTF_DIR)/ft_printf.c \
				$(PRINTF_DIR)/ft_u.c \
				$(PRINTF_DIR)/len_itoa.c \
				$(PRINTF_DIR)/len_putchar.c \
				$(PRINTF_DIR)/len_putstr.c \
				$(PRINTF_DIR)/printf_itoa.c

PRINTF_OBJ = $(PRINTF_SRC:.c=.o)

#next line unneccessary 
Cur_dir = $(shell pwd)

Objects = $(Sources:.c=.o)
bon_obj = $(bon_src:.c=.o)

CC = cc

Cflags = -Wall -Werror -Wextra

all: $(PRINTF_OBJ) $(NAME)
 
$(NAME): $(Objects) 
	@ar -src $@ $(Objects) $(PRINTF_OBJ)
	@echo $(NAME) created

$(Objects):
	@$(CC) -c $(Cflags) $(Sources)

$(PRINTF_OBJ):
	$(MAKE) -C printf

bonus: $(bon_obj) all
	@ar -src $(NAME) $(bon_obj)
	@echo bonus added to $(NAME)
	@echo $(NAME) ran with bonus

$(bon_obj):
	@$(CC) -c $(Cflags) $(bon_src)

clean:
	@rm -rf *.o
	$(MAKE) -C $(PRINTF_DIR) clean
	@echo "clean done"


fclean: clean
	@rm -f $(NAME)
	$(MAKE) -C $(PRINTF_DIR) fclean
	@echo "fclean done"


re: fclean all
	@echo "recompilation done"


seelib:
	@ar -t $(NAME)

norm: $(Sources)
	@norminette -R CheckForbiddenSourceHeader $(Sources)
	@echo all sources checked with norminette


normb: norm
	@norminette -R CheckForbiddenSourceHeader $(bon_src)
	@echo all functions checked with norminette including bonus

.PHONY: all bonus clean fclean re seelib norm normb