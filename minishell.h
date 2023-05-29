/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkurnava <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 15:41:56 by qtran             #+#    #+#             */
/*   Updated: 2023/05/29 18:48:45 by rkurnava         ###   ########.fr       */
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
typedef struct s_data
{
	char				**env_copy;
	char				*line_read;
	char				**cmd_line;

	int					fd_infile;
	int					fd_outfile;
	//not quite sure if i need the pipe fd's like this
	int					fd_p_read;
	int					fd_p_write;
	struct sigaction	sa;
}						t_data;

//init.c
void					init_data(t_data *data, char **env);

//lexer.c  ______LEXER________
int						trim_spaces(t_data *data);
void					lexer(t_data *data);

//init_cmd_line.c
int						count_tokens_v2(char *str);
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
int						ft_cd(const char *path);
void					ft_echo(const char *str, int n);
void					ft_pwd(void);
void					ft_env(char **env);
void					ft_unset(char **env, char *search);

int						ft_strcmp_v2(char *s1, char *s2);
int						syntaxer(char **cmd_line);
void					executer(t_data *data);

#endif
