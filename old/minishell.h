/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qtran <qtran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 18:08:09 by rkurnava          #+#    #+#             */
/*   Updated: 2023/06/30 15:22:45 by qtran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

# define PROMPT "\e[0;93m⮡\e[0;91m mini_hell \e[0m"
# define HERE_DOC ".heredoc"
# define TRUE 1
# define FALSE 0
# define ERROR -1

// exit statuses
# define CTRL_C 130
# define CMD_N_F 127
# define IS_DIR 126
# define NO_RIGHTS 126

// Global variable
extern int				g_ex_status;

// Structures
typedef struct s_node
{
	int					special;
	int					runnable;
	char				*cmd;
	struct s_node		*next;
	struct s_node		*prev;
}						t_node;

typedef struct s_data
{
	char				**env_copy;
	char				*line_read;
	int					children;
	int					fd_infile;
	int					fd_outfile;
	int					fd_pipe[2];
	int					fd_heredoc;
	int					problem;
	int					no;
	int					red_status;
	int					pipe_status;
	struct sigaction	sa;
	t_node				*cmd_line;
	int					pid;
}						t_data;

// main.c
int						loop_each_cmd(t_data *data);
void					eof(t_data *data);
void					init_data(t_data *data, char **env);
void					minishell_core(t_data *data);

// lexer.c
int						trim_spaces(t_data *data);
void					lexer(t_data *data);

// parser.c
int						parser(t_node *list);

// init_cmd_line.c
int						get_token_len(char *str);
int						get_non_quote_len(char *str);
int						get_quote_len(char *str);
void					init_cmd_line(t_data *data);

// token.c
void					identify_tokens(t_node *head);
int						check_if_token(t_node *node, char *token);
int						check_if_any_token(t_node *node);

// pre_executer.c
void					prep_for_executer(t_node **head, t_data *data);
void					dollar_and_s_quotes(char **str, t_data *data);
void					free_and_null(char **str);

// quotes_and_dollar
int						check_if_quote_and_closed(char *str, int i);
int						single_quotes(char **str, int i, char quote);

// dollar.c
char					*get_str_before_dollar(char *str, int i);
char					*get_end_of_dollar(char *str, int i, int left_for_cut);
int						subbing_cmd_str(char **str, char *before_d,
							char *env_value, char *end_of_d);
int						subout_dollar(char **str, int i, int left_f_cut,
							t_data *data);

// dollar_env.c
char					*get_env_value(char *look_for, char **env);
char					*get_last_exit_status(char **end_of_d, int ret_value);

// heredoc.c
int						look_for_heredoc(t_data *data, t_node *head);

// heredoc_utils.c
void					clean_heredoc_child(t_data *data);
void					check_for_dollar(char **line, t_data *data);

// redirections.c
int						set_redirections(t_node *head, t_data *data);
void					cut_out_redirection(t_node **head);

// redirection_utils.c
int						close_prev_fd(int *fd);
int						reset_fds(t_data *data);
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
void					malloc_error(t_data *data);

// signals handling;
void					signal_set_up(t_data *data);
void					ft_sig_quit(int signal_num);
void					response(int signal_num);
void					ft_wait_children(t_data *data);
void					child_response(int signal_num);
void					ft_sig_quit(int signal_num);

// built-ins
void					echo_print(t_node **node, int n);
int						ft_echo(t_node **node);
int						ft_exit(t_data *data, char ***args);
int						ft_cd(t_data *data, char ***args);
int						ft_pwd(void);
int						ft_env(char **env);
int						ft_unset(t_data *data, char *search, char ***args);
int						ft_find(t_data *data, char *search);
int						ft_invalid_env(char *str);
int						was_child(t_node *current, char ***args);
// export functions
void					ft_bash(t_data *data, int command);
int						ft_export_na(char **env, int len);
int						ft_export_a(t_data *data, char ***args, t_node **node,
							int len);
int						ft_replace_existing(t_data *data, t_node *node,
							char ***args);
int						ft_strcmp_v2_until(char *s1, char *s2, char c);
int						ft_append(t_data *data, t_node *node, int y);
int						ft_invalid(char *str);

// execve
int						ft_exec(t_node *node, char **env, t_data *data);
int						ft_exec_here(char **path, t_node *node, char ***args);
int						ft_exec_path(char **env, char **path, t_node *node,
							char ***args);
char					*exec_strjoin(char *str1, char *str2);
int						arg_num(t_node *node);
int						set_stdin_out(int fd_in, int fd_out, t_data *data);
void					fill_args(t_node *node, char ***args);
int						arg_num(t_node *node);
int						before_start(t_node *node);
void					ft_access_error(t_node *node);

int						ft_strcmp_v2(char *s1, char *s2);
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
void					strcpy_wout_ind(char **str, unsigned int x);
void					four_free(char *s1, char *s2, char *s3, char *s4);
int						check_if_char_in_row(char *str, char c);
int						count_char(char *str, char c);

// check if actually called

// string_utils_2 aka "libft alike"
char					*ft_str_many_chr(char *str, char *set);
char					*ft_strjoin_3(char *s1, char *s2, char *s3);
int						len_2d_str_arr(char **str);
void					delete_cmd(t_node **head);
void					delete_til_pipe(t_node **head);

#endif
