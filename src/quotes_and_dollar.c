
#include "../minishell.h"

int	single_quotes(char **str, int i, char quote)
{
	int		len;
	char	*sec_quote;
	char	*cutted;
	char	*rest;

	sec_quote = ft_strchr(&(*str)[i + 1], quote);
	len = sec_quote - *str - 1;
	cutted = strdup_without((*str), quote, len);
	sec_quote++;
	rest = ft_strdup(sec_quote);
	if (!cutted || !rest)
	{
		if (cutted)
			free(cutted);
		free(*str);
		*str = NULL;
		return (-1);
	}
	free((*str));
	(*str) = ft_strjoin(cutted, rest);
	free(cutted);
	free(rest);
	return (len);
}

//only works with malloc'd str
//if fail then str = NULL and it will be detected
void	dollar_and_s_quotes(char **str, t_data *data)
{
	int	i;
	int	left_for_cut;

	i = 0;
	left_for_cut = FALSE;
	while ((*str) && (*str)[i])
	{
		if ((*str)[i] == '$')
			i += subout_dollar(str, i, left_for_cut, data);
		else if (left_for_cut == FALSE && (*str)[i] == '\''
				&& ft_strchr(&(*str)[i + 1], '\'') != NULL)
			i = single_quotes(str, i, '\'');
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

//used in dollar.c
int	check_if_quote_and_closed(char *str, int i)
{
	if (str[i] == '\'' && ft_strchr(&str[i + 1], '\'') != NULL)
		return (TRUE);
	else if (str[i] == '\"' && ft_strchr(&str[i + 1], '\"') != NULL)
		return (TRUE);
	return (FALSE);
}
