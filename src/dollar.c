
#include "../minishell.h"

char	*get_str_before_dollar(char *str, int i)
{
	char	*before_dollar;

	if (i != 0)
		before_dollar = ft_substr(str, 0, i - 1);
	else
		before_dollar = ft_strdup("");
	return (before_dollar);
}

char	*get_end_of_dollar(char *str, int i, int left_for_cut)
{
	char	*end;
	int		n_single;
	int		n_double;

	n_single = count_char(str, '\'');
	n_double = count_char(str, '"');
	if (left_for_cut == TRUE && n_single > 1)
		end = ft_str_many_chr(&str[i], "'\"$?<>| ");
	else if (left_for_cut == TRUE)
		end = ft_str_many_chr(&str[i], "\"$?<>| ");
	else if (n_single == 0 && n_double > 1)
		end = ft_str_many_chr(&str[i], "\"$?<>| ");
	else if (n_single <= 1 && n_double <= 1)
		end = ft_str_many_chr(&str[i], "$?<>| ");
	else
		end = ft_str_many_chr(&str[i], "'\"$?<>| ");
	return (end);
}

int	subbing_cmd_str(char **str, char *before_d, char *env_value, char *end_of_d)
{
	char	*after_d;

	if (*end_of_d != '\0')
	{
		after_d = ft_strdup(end_of_d);
		if (!after_d)
			return (1);
		free(*str);
		(*str) = ft_strjoin_3(before_d, env_value, after_d);
		if ((*str) == NULL)
			return (1);
		free(after_d);
	}
	else
	{
		free(*str);
		*str = ft_strjoin(before_d, env_value);
		if ((*str) == NULL)
			return (1);
	}
	return (0);
}

int	subout_dollar(char **str, int i, int left_f_cut, t_data *data)
{
	char	*before_d;
	char	*d_name;
	char	*env_value;
	char	*end_of_d;

	i++;
	if (ft_strchr("<>| \0", (*str)[i]) != NULL)
		return (1);
	if (left_f_cut == TRUE && ((*str)[i] == '\'' || (*str)[i] == '"'))
		return (1);
	if (check_if_quote_and_closed((*str), i) == TRUE)
		return (strcpy_wout_ind(str, i - 1, data), 0);
	before_d = get_str_before_dollar(*str, i);
	end_of_d = get_end_of_dollar(*str, i, left_f_cut);
	d_name = ft_substr(*str, i, end_of_d - &(*str)[i]);
	if ((*str)[i] == '?')
		env_value = get_last_exit_status(&end_of_d, g_quit_heredoc); //data->status);
	else
		env_value = get_env_value(d_name, data->env_copy);
	if ((!before_d) || (!end_of_d) || (!d_name) || (!env_value))
		cleanse(data);
	if (subbing_cmd_str(str, before_d, env_value, end_of_d) == 1)
		cleanse(data);
	i = ft_strlen(env_value);
	return (four_free(d_name, before_d, env_value, NULL), i);
}
