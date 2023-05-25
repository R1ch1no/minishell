/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkurnava <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 13:54:05 by qtran             #+#    #+#             */
/*   Updated: 2023/05/25 19:40:30 by rkurnava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	main(int argc, char **argv, char **env)
{
	t_data	data;

	if (argc != 1 || argv[0] == NULL)
		return (1);
	init_data(&data, env);
	signal_set_up(&data);
	//deleted the run variable, to stop the program, press Ctrl + D
	while (1)
	{
		data.line_read = readline("\e[0;93m⮡\e[0;91m mini_hell \e[0m");
		if (data.line_read == NULL)
		{
			printf("exit\n");
			cleanse(&data);
			exit(0); //exit && free (cleanup exits for now)
		}
		if (data.line_read[0] == '\0') //empty string
		{
			free(data.line_read);
			continue ;
		}
		if (data.line_read && *data.line_read)
			//checks if str is not NULL and not empty
			add_history(data.line_read);
		lexer(&data);
		free(data.line_read);
		data.line_read = NULL;
		//heredoc();
		//parser();//
		//executer();|
		free_2d_str_arr(&data.cmd_line);
	}
	//the following block ONLY WRITTEN FOR TESTING PURPOSES
	//free(data.line_read);
	cleanse(&data);
	exit(0);
	return (1);
}
