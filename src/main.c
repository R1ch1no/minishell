/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qtran <qtran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 13:54:05 by qtran             #+#    #+#             */
/*   Updated: 2023/05/21 15:16:14 by qtran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../minishell.h"

int main(int argc, char **argv, char **env)
{
    t_data data;

    if (argc != 1 || argv[0] == NULL)
        return (1);
    
    init_data(&data, env);
    while (1)
    {
        data.line_read = readline("prompt ");
        if (data.line_read == NULL)
        {
            printf("exit\n");
            cleanup(&data);
            exit(0); //exit && free (cleanup exits for now)
        }
        if (data.line_read[0] == '\0') //empty string
        {
            free(data.line_read);
            continue;
        }
        if (data.line_read && *data.line_read) //checks if str is not NULL and not empty
            add_history(data.line_read);
        lexer(&data);
        //heredoc();
        //parser();//
        
        //the following block ONLY WRITTEN FOR TESTING PURPOSES
        //free(data.line_read);
        cleanup(&data);
        exit(0);
    }
    return (1);   
}
