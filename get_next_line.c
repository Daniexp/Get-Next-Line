/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dexposit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 19:29:14 by dexposit          #+#    #+#             */
/*   Updated: 2022/02/26 22:45:41 by dexposit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	cut(char **aux_str, char *ind_line, char **result, char **rest_read)
{
	if (ind_line)
	{
		*result = ft_substr(*aux_str, 0, ind_line - *aux_str + 1);
		if (ft_strlen(*result) != ft_strlen(*aux_str))
			*rest_read = ft_substr(ind_line + 1, 0, ft_strlen(ind_line + 1));
		free(*aux_str);
		return (1);
	}
	return (0);
}

char	*end_file(char **read_str, char **aux_str, char **result)
{
	free(*read_str);
	if (*aux_str)
	{
		*result = ft_substr(*aux_str, 0, ft_strlen(*aux_str));
		free(*aux_str);
	}
	return (*result);
}
/*
static void	check(char **rest_read, char **aux_str, char **result, char *ind)
{
	*aux_str = 0;
	*result = 0;
	if (*rest_read)
	{
		*aux_str = ft_substr(*rest_read, 0, ft_strlen(*rest_read));
		free(*rest_read);
		*rest_read = NULL;
		//cut(&(*aux_str), ind, &(*result), &(*rest_read));
		if (ind)
		{
			*result = ft_substr(*aux_str, 0, ind - *aux_str + 1);
			if (ft_strlen(*result) != ft_strlen(*aux_str))
				*rest_read = ft_substr(ind + 1, 0, ft_strlen(ind + 1));
			free(*aux_str);
		}
	}
}*/

char	*get_next_line(int fd)
{
	static char	*rest_read = 0;
	char		*aux_str;
	char		*read_str;
	char		*result;
	int			cnt_bytes;

	aux_str = 0;
	result = 0;
	if (rest_read)
	{
		aux_str = ft_substr(rest_read, 0, ft_strlen(rest_read));
		free(rest_read);
		rest_read = NULL;
		cut(&aux_str, ft_strchr(aux_str, '\n'), &result, &rest_read);
	}
	//check(&rest_read, &aux_str, &result, ft_strchr(aux_str, '\n'));
	while (!result)
	{
		read_str = malloc(BUFFER_SIZE * sizeof(char) + 1);
		cnt_bytes = read(fd, read_str, BUFFER_SIZE);
		read_str[cnt_bytes] = '\0';
		if (cnt_bytes <= 0)
			return (end_file(&read_str, &aux_str, &result));
		aux_str = cat(aux_str, read_str);
		if (!cut(&aux_str, ft_strchr(aux_str, '\n'), &result, &rest_read)
			&& cnt_bytes < BUFFER_SIZE)
		{
			result = ft_substr(aux_str, 0, ft_strlen(aux_str));
			free(aux_str);
		}
		free(read_str);
	}
	return (result);
}
