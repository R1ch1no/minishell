/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qtran <qtran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 19:19:43 by qtran             #+#    #+#             */
/*   Updated: 2022/11/18 19:20:05 by qtran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1000
# endif

# include <stddef.h>

char	*get_next_line(int fd);
char	*gnl_strchr(char *s, int c);
size_t	gnl_strlen(const char *s);
char	*gnl_strjoin(char *s1, char const *s2);
char	*gnl_strjoin_extension(char *s1);
char	*gnl_substr(char const *s, unsigned int start, size_t len);

#endif
