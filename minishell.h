/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qtran <qtran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 15:41:56 by qtran             #+#    #+#             */
/*   Updated: 2023/06/03 11:00:20 by qtran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <unistd.h>

# define HERE_DOC ".here_doc.tmp"
# define TRUE 1
# define FALSE 0

# define SPECIALS "\"\'|<>"

//	int fd;
//	fd = open("nonexistent.txt", O_RDONLY);
//	CHECK(fd);

//Structures

typedef struct s_node
{
	int					special;
	char				*cmd;
	struct s_node		*next;
}						t_node;

//fd_p_read, fd_p_write : not quite sure if i need the pipe fd's like this

typedef struct s_data
{
	char				**env_copy;
	char				*line_read;
	int					fd_infile;
	int					fd_outfile;
	int					fd_p_read;
	int					fd_p_write;
	struct sigaction	sa;
	t_node				*cmd_line;
}						t_data;

//init.c
void					init_data(t_data *data, char **env);

//lexer.c  ______LEXER________
int						trim_spaces(t_data *data);
void					lexer(t_data *data);

//init_cmd_line.c
int						get_token_len(char *str);
int						get_non_quote_len(char *str);
int						get_quote_len(char *str);
void					init_cmd_line(t_data *data);

//cutting_quotes.c
int						count_char(char *str, char c);
void					cut_out_all(char *str, char c, char *cutted);
void					cut_out_all_but_last(char *str, char c, char *cutted);
void					cut_out_quotes(char **str, char c);

//__________________________GENERAL UTILS__________________________
//
//printing_utils.c
void					print_int_arr(int *arr, int size);
void					print_str_arr(char **arr);
//dup_utils.c
char					**dup_str_arr(char **ori);
//cleanup.c
void					cleanse(t_data *data);
void					free_2d_str_arr(char ***arr);
void					free_2d_str_arr_v2(char **arr);
void					free_2d_str_until(char **arr, int end);
//signals handling;
void					signal_set_up(t_data *data);
//built-ins
int						ft_cd(t_node **node);
void					ft_echo(t_node **node);
void					ft_pwd(t_node **node);
void					ft_env(char **env, t_node **node);
void					ft_unset(t_data *data, char *search, t_node **node);
//export
void					ft_export_na(char **env, t_node **node, int len);
void					ft_export_a(t_data *data, char *var, t_node **node,
							int len);
int						ft_adjust_single_quotes(char **str, t_node *node);
int						double_quotes_count(char *str);
int						single_quotes_count(char *str);
int						ft_replace_existing(t_data *data, t_node *node);

int						ft_strcmp_v2(char *s1, char *s2);
int						syntaxer(t_node *cmd_line);
void					executer(t_data *data);

//lists
int						ft_strcmp_node(t_node *node, char *s2);
void					ft_clean_cmd(t_data *data);
void					add_node_back(t_node **lst, t_node *new);
void					print_list(t_node *head);
t_node					*create_node(char *str);

//dollar_sign_file
int						get_arr_len(char **arr);


//quotes_and_dollar
int	count_char(char *str, char c);
char *strdup_without(char *src, char c, int len);
int single_quotes(char **str, int i, char quote);
char *ft_str_many_chr(char *str, char *set);
char *ft_strjoin_3(char *s1, char *s2, char *s3);
int subout_dollar(char **str, int i);
char *strcpy_wout_ind(char *str, int x);
void dollar_and_s_quotes(char **str);

#endif
