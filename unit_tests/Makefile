NAME		= quote_dollar_test

CC			= cc
CFLAGS		= -Wall -Werror -Wextra -g

SRC_PATH 	= ../src
OBJ_PATH 	= ../obj

TEST  		=	quote_dollar_test.c

SRC			= 	init.c \
				lexer.c \
				init_cmd_line.c \
				signals.c \
				env_cd_pwd.c \
				echo_unset.c \
				export.c \
				export_utils.c \
				dollar.c \
				cutting_quotes.c \
				executer.c \
				syntaxer.c \
				ft_strcmp.c \
				cleanup.c \
				dup_utils.c \
				printing_utils.c \
				string_utils.c \
				string_utils_2.c \
				linked_list_utils.c\
				linked_list_utils_two.c\
				quotes_and_dollar.c \


SRCS 		= $(addprefix $(SRC_PATH)/, $(SRC))
OBJ 		= $(SRC:.c=.o)
OBJS 		= $(addprefix $(OBJ_PATH)/, $(OBJ))

LIBFT_DIR 	= ../libft
LIBFT 		= $(LIBFT_DIR)/libft.a

.PHONY: all bonus clean fclean re aa aac va seelib norm normb
all: $(OBJ_PATH) $(NAME)

$(OBJ_PATH):
	@mkdir -p $(OBJ_PATH)

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(LIBFT) $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(TEST) -lreadline -lhistory -o $(NAME) 
	@echo "$(GREEN)Executable \"$(NAME)\" succesfully created.$(NC)"


$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)


#General
clean:
	@rm -rf $(OBJ_PATH)
	@echo "$(MAGENTA)Obj directory removed.$(NC)"
	@$(MAKE) -C $(LIBFT_DIR) clean
	@echo "$(MAGENTA)Make clean in directory "$(LIBFT_DIR)" invoked.$(NC)"

fclean: clean
	@rm -f $(NAME)
	@echo "$(MAGENTA)Deleted executable named: $(NAME)$(NC)"
	@$(MAKE) -C $(LIBFT_DIR) fclean
	@echo "$(MAGENTA)Make fclean in directory "$(LIBFT_DIR)" invoked.$(NC)"

re: fclean all
	@echo "$(GREEN)Recompilation successfully done!$(NC)"

aa: all
	@echo "$(GREEN)Executing programm with \"TEST_INPUT\" of the Makefile.$(NC)"
	./$(NAME) $(ARGV)

va: all
	make -C ./ clean
	valgrind --leak-check=full \
		--show-leak-kinds=all \
		--track-origins=yes \
		--suppressions=val_suppression_file.txt \
		./$(NAME)
#--track-fds=yes \
#code valgrind_output.txt

#--trace-children=yes
#valgrind --leak-check=full --show-leak-kinds=all ./$(NAME) $(TEST_INPUT)

debug : CFLAGS += -g
debug : fclean all

norm: $(SRCS)
	norminette -R CheckForbiddenSourceHeader $(SRCS) $(NAME).h
	@echo "$(BWHITE)All source files checked with norminette.$(NC)"









#--------COLORS---------------------------------#
RED			=	\033[0;31m
GREEN		=	\033[0;32m
YELLOW		=	\033[0;33m
BLUE 		=	\033[0;34m
MAGENTA 	=	\033[0;35m
CYAN 		=	\033[0;36m
WHITE		=	\033[0;37m
NC			=	\033[0m


#-------BOLD COLORS-----------------------------#
BRED		=	\033[1;31m
BGREEN		=	\033[1;32m
BYELLOW		=	\033[1;33m
BBLUE 		=	\033[1;34m
BMAGENTA 	=	\033[1;35m
BCYAN 		=	\033[1;36m
BWHITE		=	\033[1;37m
