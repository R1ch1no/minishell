
#include "../minishell.h"

char	*get_env_value(char *look_for, char **env)
{
	char	*env_value;
	char 	*start;
	int i;

	i = -1;
	while (env[++i])
	{
		if (ft_strncmp(look_for, env[i], ft_strlen(look_for)) == 0)
		{
			start = ft_strchr(env[i], '=');
			env_value = ft_strdup(++start);
			break;
		}
	}
	if (env[i] == NULL)
		env_value = ft_strdup("");
	if (!env_value)
		return (NULL);
	return (env_value);
}

char 	*get_last_exit_status(char **end_of_d, int ret_value)
{
	char	*status;

	if (!end_of_d)
		return (NULL);
	status = ft_itoa(ret_value);
	(*end_of_d)++;
	return (status);
}