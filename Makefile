NAME		= minishell

CC			= cc
CFLAGS		= -Wall -Werror -Wextra

SRC_PATH 	= src
OBJ_PATH 	= obj

SRC			= 	main.c \
				core_functions.c \
				core_functions_2.c \
				lexer.c \
				parser.c \
				init_cmd_line.c \
				signals.c \
				pwd_env.c \
				env_cd_pwd.c \
				echo_unset.c \
				built-in_utils.c \
				exit.c \
				export.c \
				export_utils.c \
				export_utils_two.c \
				dollar.c \
				dollar_env.c \
				pre_executer.c \
				executer.c \
				executer_utils.c \
				execve.c \
				execve_utils.c \
				execve_utils_two.c \
				ft_strcmp.c \
				cleanup.c \
				dup_utils.c \
				token.c \
				printing_utils.c \
				string_utils.c \
				string_utils_2.c \
				linked_list_utils.c\
				linked_list_utils_two.c\
				quotes_and_dollar.c \
				heredoc.c \
				heredoc_utils.c \
				redirections.c \
				redirection_utils.c

SRCS 		= $(addprefix $(SRC_PATH)/, $(SRC))
OBJ 		= $(SRC:.c=.o)
OBJS 		= $(addprefix $(OBJ_PATH)/, $(OBJ))

LIBFT_DIR 	= libft
LIBFT 		= $(LIBFT_DIR)/libft.a

.PHONY: all bonus clean fclean re aa aac va seelib norm normb
all: $(OBJ_PATH) $(NAME)

$(OBJ_PATH):
	@mkdir -p $(OBJ_PATH)

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(LIBFT) $(OBJS)
	@echo "$(BYELLOW)Creating executable:$(NC)"
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -lreadline -lhistory -o $(NAME) 
	@echo "$(GREEN)Executable \"$(NAME)\" succesfully created.$(NC)"

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)

#General
clean:
	@rm -f val_suppression_file.txt
	@rm -rf $(OBJ_PATH)
	@echo "$(MAGENTA)Obj directory removed.$(NC)"
	@$(MAKE) -C $(LIBFT_DIR) clean
	@echo "$(MAGENTA)Make clean in directory "$(LIBFT_DIR)" invoked.$(NC)"

fclean:
	@rm -f val_suppression_file.txt
	@rm -rf $(OBJ_PATH)
	@echo "$(MAGENTA)Obj directory removed.$(NC)"
	@rm -f $(NAME)
	@echo "$(MAGENTA)Deleted executable named: $(NAME)$(NC)"
	@$(MAKE) -C $(LIBFT_DIR) fclean
	@echo "$(MAGENTA)Make fclean in directory "$(LIBFT_DIR)" invoked.$(NC)"

re: fclean all
	@echo "$(GREEN)Recompilation successfully done!$(NC)"

va: all
	touch val_suppression_file.txt
	echo >> val_suppression_file.txt {
	echo >> val_suppression_file.txt 	leak readline
	echo >> val_suppression_file.txt	 Memcheck:Leak
	echo >> val_suppression_file.txt 	...
	echo >> val_suppression_file.txt	fun:readline
	echo >> val_suppression_file.txt }
	echo >> val_suppression_file.txt {
	echo >> val_suppression_file.txt	leak add_history
	echo >> val_suppression_file.txt	Memcheck:Leak
	echo >> val_suppression_file.txt	...
	echo >> val_suppression_file.txt	fun:add_history
	echo >> val_suppression_file.txt }
	valgrind \
	--leak-check=full \
	--show-leak-kinds=all \
	--track-origins=yes \
	--verbose \
	--track-fds=yes \
	--suppressions=val_suppression_file.txt \
	./$(NAME)
#--log-file=valgrind_output.txt \

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
