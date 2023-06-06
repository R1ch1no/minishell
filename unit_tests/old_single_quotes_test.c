/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_quotes_test.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qtran <qtran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 14:49:08 by qtran             #+#    #+#             */
/*   Updated: 2023/06/03 12:18:30 by qtran            ###   ########.fr       */
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

int single_quotes(char **str, int i)
{
    int len;
    char *sec_quote;
    char *cutted;
    char *rest;
    
    i++;
    sec_quote = ft_strchr(&(*str)[i], '\'');
    if (sec_quote != NULL)
    {
        len = sec_quote - (*str) - 1;
        cutted = strdup_without((*str), '\'', len);
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

int subout_dollar(char **str, int i)
{
    char *before_dollar;
    char *dollar_name;
    char *env_value;
    char *end;
    char *temp;

    if (i != 0)
        before_dollar = ft_substr(*str, 0, i);
    else
        before_dollar = ft_strdup("");
    //it can have spaces and <> signs if its in double quotes, bash reads the name until the special chars
    //currently still a bug if $name" or $"nameand unclosed quote
    if (count_char(*str, '\'') % 2 != 0 || (count_char(*str, '\"') == 1))
        end = ft_str_many_chr(&(*str)[i + 1], "$ "); 
    else
        end = ft_str_many_chr(&(*str)[i + 1], "$'\" ");
    
    dollar_name = ft_substr(*str, i + 1, end - &(*str)[i + 1]);
    //printf("dollar_name: %s\n", dollar_name);
    env_value = ft_strdup("qtran");
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

char *strcpy_wout_ind(char *str, int x)
{
    int i;
    int j;
    char *cpy;
        
    if (!str)
        return (NULL);
    cpy = malloc(sizeof(char) * ft_strlen(str));
    if (!cpy)
        exit(1);
    i = 0;
    j = 0;
    while (str[i])
    {
        if (i != x)
        {
            cpy[j] = str[i];
            i++;
            j++;
        }
        else
            i++;   
    }
    cpy[j] = '\0';
    return (cpy);
}


//only works with malloc'd str
void dollar_and_s_quotes(char **str) 
{
    int i;
    char *temp;

    i = 0;
    while ((*str)[i])
    {
        if ((*str)[i] == '$' && (*str)[i + 1] && (*str)[i + 1] != ' ')
        {
            if ((*str)[i + 1] == '?')
                printf("Baustelle\n");
            if (((*str)[i + 1] == '\'' && ft_strchr(&(*str)[i + 2], '\'')) || 
                ((*str)[i + 1] == '\"' && ft_strchr(&(*str)[i + 2], '\"')))
            {
                temp = strcpy_wout_ind(*str, i);
                free(*str);
                *str = temp;
                printf("Baustelle quotes nach $\n");
                i++;
            }
            else
                i = subout_dollar(str, i);
        }  
        else if ((*str)[i] == '\'') 
            i = single_quotes(str, i);
        else
            i++;
    }
}


int main()
{
    //strdup_without
    //char *str = "Hell' mini'shell";
    //printf("Input str: %s\n", str);
    //char *dup = get_str_wihtout(str);
    //printf("Input str: %s\n", str);
    //printf("dup: %s\n", dup);
    //free(dup);

    //char *str = "second'test'2 single 'quotes before and at end 3'";
    //char *str2 = strdup(str);
    //printf("Input str: %s\n", str2);
    //char *dup2 = get_str_wihtout(str2);
    //printf("Input str: %s\n", str2);
    //printf("dup: %s\n", dup2);
    //free(dup2);

    //dollar substitute function
    /* char *str3 = ft_strdup("01$USERSHIT>name");
    printf("Original: %s\n", str3);
    subout_dollar(&str3, 2);
    printf("%s\n", str3);
    free(str3); */

    //TESTING ACTUAL IMPLEMENTATION FOR MINISHELL
    char *str3 = ft_strdup("01'$USER'SHIT $USER$USER'''$'user");
    printf("Original: %s\n", str3);
    dollar_and_s_quotes(&str3);
    printf("changed: %s\n", str3);
    free(str3);
    //dollar in d und s quotes
    str3 = ft_strdup("test'$'");
    printf("Original: %s\n", str3);
    dollar_and_s_quotes(&str3);
    printf("changed: %s\n", str3);
    free(str3);
    
    str3 = ft_strdup("$smth'$' money");
    printf("Original: %s\n", str3);
    dollar_and_s_quotes(&str3);
    printf("changed: %s\n", str3);
    free(str3);
    
    //dollar at end 
    str3 = ft_strdup("name$");
    printf("Original: %s\n", str3);
    dollar_and_s_quotes(&str3);
    printf("changed: %s\n", str3);
    free(str3);

    //str3 = ft_strdup("bashtest$\"quotes\"");
    //printf("Original: %s\n", str3);
    //dollar_and_s_quotes(&str3);
    //printf("changed: %s\n", str3);
    //free(str3);


    //$-sign and after quote which is closed
    str3 = ft_strdup("bashtest$\"quotes\"");
    printf("Original: %s\n", str3);
    dollar_and_s_quotes(&str3);
    printf("changed: %s\n", str3);
    free(str3);

    printf("\n----$-sign and after it a quote which is unlcosed----\n");
    //str3 = ft_strdup("bashtest$\"quotes");
    str3 = ft_strdup("test$USER\"");
    printf("Original: %s\n", str3);
    dollar_and_s_quotes(&str3);
    printf("changed: %s\n", str3);
    free(str3);
    printf("\n----$-sign and after it 3 quotes----\n");
    str3 = ft_strdup("test$USER\"three\"quo\"tes");
    printf("Original: %s\n", str3);
    dollar_and_s_quotes(&str3);
    printf("changed: %s\n", str3);
    free(str3);


    printf("\n----closed quote after dollar----\n");
    //str3 = ft_strdup("bashtest$\"quotes");
    str3 = ft_strdup("test$USER\"NAME\"");
    printf("Original: %s\n", str3);
    dollar_and_s_quotes(&str3);
    printf("changed: %s\n", str3);
    free(str3);

    printf("\n----redirection with quotes and without---\n");
    //str3 = ft_strdup("bashtest$\"quotes");
    str3 = ft_strdup("bashtest\"$USER>name\"");
    printf("Original: %s\n", str3);
    dollar_and_s_quotes(&str3);
    printf("changed: %s\n", str3);
    free(str3);
    str3 = ft_strdup("bashtest$USER>name");
    printf("Original: %s\n", str3);
    dollar_and_s_quotes(&str3);
    printf("changed: %s\n", str3);
    free(str3);
    
    str3 = ft_strdup("$\"USER\"");
    printf("Original: %s\n", str3);
    dollar_and_s_quotes(&str3);
    printf("changed: %s\n", str3);
    free(str3);
}
