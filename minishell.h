
#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

# define HERE_DOC ".heredoc"
# define TRUE 1
# define FALSE 0
# define ERROR -1

# define SPECIALS "\"\'|<>"

//	int fd;
//	fd = open("nonexistent.txt", O_RDONLY);
//	CHECK(fd);
//Global variable

extern int quit_heredoc; 

// Structures
typedef struct s_node
{
	int					special;
	int					runnable;
	char				*cmd;
	struct s_node		*next;
	struct s_node		*prev;
}						t_node;

// fd_p_read, fd_p_write : not quite sure if i need the pipe fd's like this
typedef struct s_data
{
	char				**env_copy;
	char				*line_read;
	int					children;
	int					fd_infile;
	int					fd_outfile;
	int					fd_pipe[2];
	int					fd_heredoc;
	struct sigaction	sa;
	t_node				*cmd_line;
	int					pid;
}						t_data;

// main.c
void					loop_each_cmd(t_data *data);

// init.c
void					init_data(t_data *data, char **env);

// lexer.c
int						trim_spaces(t_data *data);
void					lexer(t_data *data);

// parser.c
int						parser(t_node *list);
int						check_if_token(t_node *node, char *token);
int						check_if_any_token(t_node *node);

// init_cmd_line.c
int						get_token_len(char *str);
int						get_non_quote_len(char *str);
int						get_quote_len(char *str);
void					init_cmd_line(t_data *data);

// token.c
void					identify_tokens(t_node *head);

// pre_executer.c
void					prep_for_executer(t_node **head, t_data *data);
void					dollar_and_s_quotes(char **str, t_data *data);

// cutting_quotes.c not used yet maybe unneccassary
int						count_char(char *str, char c);
void					cut_out_all(char *str, char c, char *cutted);
void					cut_out_all_but_last(char *str, char c, char *cutted);
void					cut_out_quotes(char **str, char c);

// quotes_and_dollar
// dollar.c
char					*get_str_before_dollar(char *str, int i);
char					*get_end_of_dollar(char *str, int i, int left_for_cut);
char					*get_env_value(char *look_for, char c, char **end_of_d,
							char **env);
int						subbing_cmd_str(char **str, char *before_d,
							char *env_value, char *end_of_d);
int						subout_dollar(char **str, int i, int left_f_cut,
							t_data *data);

// heredoc.c
int						look_for_heredoc(t_data *data, t_node *head);

// redirections.c
int						set_redirections(t_node *head, t_data *data);
void					cut_out_redirection(t_node **head);

// redirection_utils.c
int						close_prev_fd(int *fd);
int						reset_in_out_stream(t_data *data);
int						open_pipe(t_data *data);
int						close_pipe(t_data *data);

//__________________________GENERAL UTILS__________________________
//
// printing_utils.c
void					print_int_arr(int *arr, int size);
void					print_str_arr(char **arr);
// dup_utils.c
char					**dup_str_arr(char **ori);
// cleanup.c
void					cleanse(t_data *data);
void					free_2d_str_arr(char ***arr);
void					free_2d_str_arr_v2(char **arr);
void					free_2d_str_until(char **arr, int end);
// signals handling;
void					signal_set_up(t_data *data);
void					ft_sig_quit(int signal_num);
void					response(int signal_num);
void					ft_wait_children(t_data *data);

// built-ins
int						ft_cd(t_node **node);
int						ft_pwd(void);
int						ft_echo(t_node **node);
void					echo_print(t_node **node, int n);
int						ft_env(char **env);
int						ft_unset(t_data *data, char *search);
// export functions
void					ft_bash(t_data *data, int command);
int						ft_export_na(char **env, int len);
int						ft_export_a(t_data *data, char *var, t_node **node,
							int len);
int						ft_replace_existing(t_data *data, t_node *node);
int						ft_strcmp_v2_until(char *s1, char *s2, char c);
int						ft_append(t_data *data, t_node *node, int y);

// execve
int						ft_exec(t_node *node, char **env);
int						ft_exec_here(char **path, t_node *node, char ***args);
int						ft_exec_path(char **pre_path, char **path, t_node *node,
							char ***args);
char					*exec_strjoin(char *str1, char *str2);
int						arg_num(t_node *node);
int						set_stdin_out(int fd_in, int fd_out, t_data *data);
// quotes utils
int						double_quotes_count(char *str);
int						single_quotes_count(char *str);
int						closed_with_double(char *str);
int						closed_with_single(char *str);

int						ft_strcmp_v2(char *s1, char *s2);
int						syntaxer(t_node *cmd_line);
int						executer(t_data *data);

// lists
int						ft_strcmp_node(t_node *node, char *s2);
void					ft_clean_cmd(t_data *data);
void					add_node_back(t_node **lst, t_node *new);
void					print_list(t_node *head);
t_node					*create_node(char *str);
void					delete_node(t_node *delete, t_node **head);

// dollar_sign_file
int						get_arr_len(char **arr);

// string_utils
char					*strdup_without(char *src, char c, int len);
void					strcpy_wout_ind(char **str, unsigned int x,
							t_data *data);
int	check_if_char_in_row(char *str, char c); // check if actually called
void					four_free(char *s1, char *s2, char *s3, char *s4);

// string_utils_2 aka "libft alike"
char					*ft_str_many_chr(char *str, char *set);
char					*ft_strjoin_3(char *s1, char *s2, char *s3);

#endif
