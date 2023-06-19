/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_checks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qtran <qtran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 11:19:44 by qtran             #+#    #+#             */
/*   Updated: 2023/04/30 17:15:51 by qtran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int check_if_even_amount(char *str, char c)
{
    int i;
    int count;

    i = 0;
    count = 0;
    while (str[i])
    {
        if (str[i] == c)
            count++;
        i++;
    }
    if (count % 2 == 0) //0 % 2 = 0 so if no quotes it also returns 1
        return (1);
    return (0);
}

int check_for_quotes(char *line_read)
{
    if (!(check_if_even_amount(line_read, '\'') && check_if_even_amount(line_read, '\"')))
        return (printf("Uneven quote amount!\n"), 1);
    return (0);
}
