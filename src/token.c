/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkurnava <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 18:06:04 by rkurnava          #+#    #+#             */
/*   Updated: 2023/07/17 15:34:45 by rkurnava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	identify_tokens(t_node *head)
{
	t_node	*current;

	current = head;
	while (current)
	{
		if (ft_strcmp_v2(current->cmd, "<") == 0 || ft_strcmp_v2(current->cmd,
				"<<") == 0)
			current->special = TRUE;
		else if (ft_strcmp_v2(current->cmd, ">") == 0
			|| ft_strcmp_v2(current->cmd, ">>") == 0)
			current->special = TRUE;
		else if (ft_strcmp_v2(current->cmd, "|") == 0)
			current->special = TRUE;
		current = current->next;
	}
}

int	check_if_token(t_node *node, char *token)
{
	if (!node || node == NULL || !token)
		return (FALSE);
	if (ft_strcmp_v2(node->cmd, token) == 0 && node->special == 1)
		return (TRUE);
	return (FALSE);
}

int	check_if_any_token(t_node *node)
{
	if (!node)
		return (FALSE);
	if (check_if_token(node, "|") == TRUE)
		return (TRUE);
	if (check_if_token(node, "<") == TRUE)
		return (TRUE);
	if (check_if_token(node, "<<") == TRUE)
		return (TRUE);
	if (check_if_token(node, ">") == TRUE)
		return (TRUE);
	if (check_if_token(node, ">>") == TRUE)
		return (TRUE);
	return (FALSE);
}

int	export_thing(t_data *data, char ***args, char ***prev_args)
{
	int		y;
	int		len;
	char	**new_env;

	len = get_arr_len(data->env_copy) + 1;
	new_env = copy_2d_char_arr(data->env_copy, len);
	if (new_env == NULL || !new_env)
		return (free_2d_str_arr(args), free_2d_str_arr(prev_args), malloc_error(data), 1);
	y = get_arr_len(new_env);
	new_env[y] = malloc(ft_strlen((*args)[0]) + 1);
	if (new_env[y] == NULL || !new_env[y])
		return (free_2d_str_arr(&new_env), free_2d_str_arr(args), free_2d_str_arr(prev_args),
			malloc_error(data), 1);
	ft_strlcpy(new_env[y], (*args)[0], ft_strlen((*args)[0]) + 1);
	new_env[y + 1] = NULL;
	free_2d_str_arr(&data->env_copy);
	data->env_copy = new_env;
	return (0);
}
