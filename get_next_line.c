/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dexposit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 19:29:14 by dexposit          #+#    #+#             */
/*   Updated: 2022/02/26 19:17:47 by dexposit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
/*
 *	STEPS:
 *		Crear línea a devolver.
 *			linea = rest_read concatenado con read_str
 *			hasta que encuentre un \n o final del archivo (cnt_bytes == 0)
 *		1- Usar read para saber si queda por leer o no del archivo.
 *		2- Buscar un \n 
 *
 */

char	*cat(char *first, char *end)
{
	char	*res;
	size_t	len;

	if (!first)
	{
		free(first);
		res = ft_substr(end, 0, ft_strlen(end));
		if (!res)
			return (0);
	}
	else
	{
		len = 1 + ft_strlen(first) + ft_strlen(end);
		res = malloc(sizeof(char) * len);
		if (!res)
			return (0);
		ft_memcpy(res, first, ft_strlen(first));
		ft_memcpy(res + ft_strlen(first), end, ft_strlen(end));
		res[len - 1] = '\0';	
		free(first);
	}
	return (res);
}

char	*get_next_line(int fd)
{
	static char	*rest_read = 0;
	char		*aux_str;
	char		*read_str;
	char		*result;
	int			cnt_bytes;
	

	if (fd < 0)
		return (0);
	aux_str = 0;
	result = 0;
	if (rest_read)
		aux_str = ft_substr(rest_read, 0, ft_strlen(rest_read));
	if (aux_str)
	{
		free(rest_read);
		rest_read = NULL;
		if (ft_strchr(aux_str, '\n')/* && *aux_str*/)
			{
				result = ft_substr(aux_str, 0, ft_strchr(aux_str, '\n') - aux_str + 1);
				if (!result)
					return (0);
				if (ft_strlen(result) != ft_strlen(aux_str))
					rest_read = ft_substr(ft_strchr(aux_str, '\n') + 1, 0, ft_strlen(ft_strchr(aux_str, '\n') + 1));
//				ft_memcpy(rest_read, ft_strchr(aux_str, '\n') + 1, ft_strlen(ft_strchr(aux_str, '\n') + 1));
				free(aux_str);
			}
	}
	while (!result)
	{
		read_str = malloc(BUFFER_SIZE * sizeof(char) + 1);
		if (!read_str)
			return (0);
		cnt_bytes = read(fd, read_str, BUFFER_SIZE);
		if (cnt_bytes <= 0)
		{
			free(read_str);
			if (aux_str)
			{
				result = ft_substr(aux_str, 0, ft_strlen(aux_str));
				free(aux_str);
			}
			if (!aux_str)
			{
			free(result);
			result = NULL;
			}
			return (result);
			//break ;
		}
		read_str[cnt_bytes] = '\0';
			aux_str = cat(aux_str, read_str);
			if (ft_strchr(aux_str, '\n'))
			{
				result = ft_substr(aux_str, 0, ft_strchr(aux_str, '\n') - aux_str + 1);
				if (!result)
					return (0);
				if (ft_strlen(result) != ft_strlen(aux_str))
					rest_read = ft_substr(ft_strchr(aux_str, '\n') + 1, 0, ft_strlen(ft_strchr(aux_str, '\n') + 1));
				free(aux_str);
			}
			else if (cnt_bytes < BUFFER_SIZE)
		{
			result = ft_substr(aux_str, 0, ft_strlen(aux_str));
			free(aux_str);
			free(rest_read);
			rest_read = NULL;
		}
		free(read_str);
	}
	return (result);
}
