/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_and_dollar.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qtran <qtran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 14:49:08 by qtran             #+#    #+#             */
/*   Updated: 2023/06/05 16:20:25 by qtran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

# include "../libft/libft.h"

# define TRUE 1
# define FALSE 0

void strcpy_wout_ind(char **str, unsigned int x);


char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
    if (!s)
        return (NULL);
	while (s[i] && s[i] != (char)c)
		i++;
	if (s[i] == (char)c)
		return ((char *)(&s[i]));
	else
		return (NULL);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	j = 0;
	if (!s1 || !s2)
		return (0);
	str = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!str)
		return (0);
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		str[i + j] = s2[j];
		j++;
	}
	str[i + j] = '\0';
	return (str);
}

int	count_char(char *str, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	if (!str)
		return (-1);
	while (str[i])
	{
		if (str[i] == c)
			count++;
		i++;
	}
	return (count);
}


char *strdup_without(char *src, char c, int len)
{
    char *dup;
    int i;
    int j;

    if (!src)
        return (NULL);
    dup = malloc(sizeof(char) * (len + 1));
    if (!dup)
        exit(1); //cleanse()
    i = 0;
    j = 0;
    while (src[i] && j < len)
    {
        if (src[i] != c)
        {
            dup[j] = src[i];
            j++;
        }
        i++;
    }
    dup[j] = '\0';
    return (dup);
}

int single_quotes(char **str, int i, char quote, t_data *data)
{
    int len;
    char *sec_quote;
    char *cutted;
    char *rest;
    
    i++;
    sec_quote = ft_strchr(&(*str)[i], quote);
    if (sec_quote != NULL)
    {
        len = sec_quote - (*str) - 1;
        cutted = strdup_without((*str), quote, len);
        sec_quote++;
        rest = strdup(sec_quote);
        free((*str));
        (*str) = ft_strjoin(cutted, rest);
        free(cutted);
        free(rest);
        i = len;
    }
    return (i);
    //printf("len: %d\n", len);
        //printf("cutted: %s\n", cutted);
        //printf("rest: %s\n", rest);
}

char *ft_str_many_chr(char *str, char *set)
{
    int i;
    int j;

    if (!str || !set)
        return (NULL);
    i = 0;
    j = 0;
    while (str[i])
    {
        while (set[j])
        {
            if (str[i] == set[j])
                return (&str[i]);
            j++;
        }
        j = 0;
        i++;
    }
    return (&str[i]);
}


char *ft_strjoin_3(char *s1, char *s2, char *s3)
{
    char *str;
    char *temp;
    
    if (!s1 || !s2 || !s3)
        return (NULL);
    temp = ft_strjoin(s1, s2);
    if (!temp)
        return (NULL);
    str = ft_strjoin(temp, s3);
    free(temp);
    if (!str)
        return (NULL);
    return (str);
}

int check_if_char_in_row(char *str, char c)
{
    int i;
    
    i = 0;
    
    if (!str)
        return (-1);
    if (str[i] == c && str[i + 1] == c)
        return (TRUE);
    else
        return(FALSE);
}

char *get_str_before_dollar(char *str, int i)
{
    char *before_dollar;
    if (i != 0)
        before_dollar = ft_substr(str, 0, i - 1);
    else
        before_dollar = ft_strdup("");
    return (before_dollar);
}

//it can have spaces and <> signs if its in double quotes, bash reads the name until the special chars
//fixes bug if unclosed quote after $ sign: $name" or $"name 
char *get_end_of_dollar(char *str, int i)
{
    char *end;
    
    if (count_char(str, '\'') == 1 || count_char(str, '\"') == 1)
        end = ft_str_many_chr(&str[i], "$?<>| ");
    else
        end = ft_str_many_chr(&str[i], "'\"$?<>| ");
    return (end);
}

char *get_env_value(char c, char **end_of_d)
{
    char *env_value;
    
    if (c == '?')
    {
        env_value = ft_strdup("1234");
        (*end_of_d)++;
    }
    else
        env_value = ft_strdup("qtran");
    return (env_value);
}

int subbing_cmd_str(char **str, char *before_d, char *env_value, char *end_of_d)
{
    char *after_d;
    
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

int subout_dollar(char **str, int i, t_data *data)
{
    char *before_d;
    char *d_name;
    char *env_value;
    char *end_of_d;

    i++;
    if (!(*str)[i] || ft_strchr("<>| ", (*str)[i]) != NULL)
        return (i);
    if (((*str)[i] == '\'' && ft_strchr(&(*str)[i + 1], '\'')) || 
        ((*str)[i] == '\"' && ft_strchr(&(*str)[i + 1], '\"')))
        return (strcpy_wout_ind(str, i - 1), i - 1);
    before_d = get_str_before_dollar(*str, i);
    end_of_d = get_end_of_dollar(*str, i);
    d_name = ft_substr(*str, i, end_of_d - &(*str)[i]);
    env_value = get_env_value((*str)[i], &end_of_d);
    if ((!before_d) || (!end_of_d) || (!d_name) || (!env_value))
        cleanse(data);
    if (subbing_cmd_str(str, before_d, env_value, end_of_d) == 1)
        cleanse(data);
    i += ft_strlen(env_value) - 1;
    free(d_name);
    free(before_d);
    free(env_value);
    return (i);
}

void strcpy_wout_ind(char **str, unsigned int x, t_data *data)
{
    unsigned int i;
    unsigned int j;
    char *cpy;
        
    cpy = malloc(sizeof(char) * ft_strlen(*str));
    if (!cpy)
        cleanse(data);
    i = 0;
    j = 0;
    while ((*str)[i])
    {
        if (i != x)
        {
            cpy[j] = (*str)[i];
            i++;
            j++;
        }
        else
            i++;   
    }
    cpy[j] = '\0';
    free(*str);
    *str = cpy;
}

//only works with malloc'd str
//j is to "remember" the ending double quote if before it is $ then skip substitution and to not subout single quotes
void dollar_and_s_quotes(char **str) 
{
    int i;
    int last_quote;
    
    i = 0;
    last_quote = 0;
    while ((*str)[i])
    {
        if ((*str)[i] == '$' && last_quote - 1 != i)//&& (*str)[i + 1] && (*str)[i + 1] != ' ' )
        {
            //if (i < last_quote)
            i = subout_dollar(str, i, t_data *data);
        }  
        else if ((*str)[i] == '\'') // && last_quote - 1 < i) //muss noch gefixed werden
            i = single_quotes(str, i, '\'');
        else if ((*str)[i] == '\"')
        {
            last_quote = single_quotes(str, i, '\"');
            if ((*str)[i] == '\"')
                i++;        
        }
        else
            i++;
    }
}
