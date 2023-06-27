
#include "../minishell.h"

void	s__d_quotes(char **str, t_data *data)
{
	int	i;
	int	left_for_cut;

	i = 0;
	left_for_cut = FALSE;
	while ((*str) && (*str)[i])
	{
		if (left_for_cut == FALSE && (*str)[i] == '\'' && ft_strchr(&(*str)[i
			+ 1], '\'') != NULL)
			i += single_quotes(str, i, '\'');
		else if ((*str)[i] == '"' && left_for_cut == TRUE)
		{
			strcpy_wout_ind(str, i, data);
			left_for_cut = FALSE;
		}
		else if ((*str)[i] == '"' && ft_strchr(&(*str)[i + 1], '"') != NULL)
		{
			strcpy_wout_ind(str, i, NULL);
			left_for_cut = TRUE;
		}
		else
			i++;
	}
}
//"$USER"te"st
void	prep_for_executer(t_node **head, t_data *data)
{
	t_node	*current;

	current = *head;
	while (current)
	{
		if ((count_char(current->cmd, '\'') > 1 || count_char(current->cmd,
					'"') > 1 || ft_strchr(current->cmd, '$') != NULL)
					&& check_if_token(current->prev, "<<") == FALSE)
			dollar_and_s_quotes(&(current->cmd), data);
		s__d_quotes(&current->cmd, data);
		//if ((count_char(current->cmd, '\'') > 1 || count_char(current->cmd,
		//			'"') > 1 || ft_strchr(current->cmd, '$') != NULL)
		//	&& check_if_token(current->prev, "<<") == TRUE)
		//	s__d_quotes(&current->cmd, data);
		//else
		//	dollar_and_s_quotes(&(current->cmd), data);
		current = current->next;
	}
}
