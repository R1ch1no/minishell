/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qtran <qtran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 15:41:56 by qtran             #+#    #+#             */
/*   Updated: 2023/05/21 17:05:28 by qtran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_H
# define MINI_H

# include "libft/libft.h"
# include <readline/history.h>
# include <readline/readline.h>
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
	char	**env_copy;
	char	*line_read;
	char	**cmd_line;

	int		fd_infile;
	int		fd_outfile;
	//not quite sure if i need the pipe fd's like this
	int		fd_p_read;
	int		fd_p_write;
}			t_data;

//init.c
void		init_data(t_data *data, char **env);

//lexer.c  ______LEXER________
void		lexer(t_data *data);
int trim_spaces(t_data *data);

//init_cmd_line.c
int count_tokens_v2(char *str);
void init_cmd_line(t_data *data);
int get_token_len(char *str);
int get_non_quote_len(char *str);
int get_quote_len(char *str);






//__________________________GENERAL UTILS__________________________
//
//printing_utils.c
void		print_int_arr(int *arr, int size);
void		print_str_arr(char **arr);
//dup_utils.c
char		**dup_str_arr(char **ori);
//cleanup.c
void		cleanup(t_data *data);
void		free_2d_str_arr(char **arr);
void 		free_2d_str_until(char **arr, int end);


#endif