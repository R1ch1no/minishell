/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_and_dollar.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qtran <qtran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 14:49:08 by qtran             #+#    #+#             */
/*   Updated: 2023/06/03 13:24:12 by qtran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

# include "../libft/libft.h"

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i] != (char)c && s[i])
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

int single_quotes(char **str, int i, char quote)
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
    str = ft_strjoin(temp, s3);
    free(temp);
    return (str);
}



int check_if_char_in_row()
{
    
}

int subout_dollar(char **str, int i)
{
    char *before_dollar;
    char *dollar_name;
    char *env_value;
    char *end;
    char *temp;


    if ((*str)[i + 1] == '\"' && (*str)[i + 2] == '\"')
        return (i+=2);
    if (ft_strchr("<>|", (*str)[i + 1]) != NULL)
            return (i++);
    if (i != 0)
        before_dollar = ft_substr(*str, 0, i);
    else
        before_dollar = ft_strdup("");
    //it can have spaces and <> signs if its in double quotes, bash reads the name until the special chars
    //fixes bug if unclosed quote after $ sign: $name" or $"name 
    if (count_char(*str, '\'') == 1 || count_char(*str, '\"') == 1)
        end = ft_str_many_chr(&(*str)[i + 1], "$?<>| ");
    else
        end = ft_str_many_chr(&(*str)[i + 1], "'\"$?<>| ");
    
    dollar_name = ft_substr(*str, i + 1, end - &(*str)[i + 1]);
    if (strcmp(dollar_name, "?") == 0)
        env_value = ft_strdup("1234");
    else
        env_value = ft_strdup("qtran");
    printf("dallor name: %s\n", dollar_name);
    printf("env value: %s\n", env_value);
    if (*end != '\0')
    {
        temp = ft_strdup(end++);
        free(*str);
        (*str) = ft_strjoin_3(before_dollar, env_value, temp);
        free(temp);
    }
    else
    {
        free(*str);
        *str = ft_strjoin(before_dollar, env_value);
    }
    i += (ft_strlen(env_value));
    free(dollar_name);
    free(before_dollar);
    free(env_value);
    return (i);
}

void strcpy_wout_ind(char **str, unsigned int x)
{
    unsigned int i;
    unsigned int j;
    char *cpy;
        
    cpy = malloc(sizeof(char) * ft_strlen(*str));
    if (!cpy)
        exit(1);
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
void dollar_and_s_quotes(char **str) 
{
    int i;

    i = 0;
    while ((*str)[i])
    {
        if ((*str)[i] == '$' && (*str)[i + 1] && (*str)[i + 1] != ' ')
        {
            if ((*str)[i + 1] == '?')
                printf("Baustelle\n");
            if (((*str)[i + 1] == '\'' && ft_strchr(&(*str)[i + 2], '\'')) || 
                ((*str)[i + 1] == '\"' && ft_strchr(&(*str)[i + 2], '\"')))
                strcpy_wout_ind(str, i);
            else
                i = subout_dollar(str, i);
        }  
        else if ((*str)[i] == '\'') 
            i = single_quotes(str, i, '\'');
        else if ((*str)[i] == '\"')
        {
            single_quotes(str, i, '\"');
            if ((*str)[i] == '\"')
                i++;        
        }
        else
            i++;
    }
}
