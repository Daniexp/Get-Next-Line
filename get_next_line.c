/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dexposit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 19:29:14 by dexposit          #+#    #+#             */
/*   Updated: 2022/02/24 21:03:36 by dexposit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/*
 *	STEPS:
 *		- read the size of the BUFFER_SIZE
 *		- concat static variable with read_str
 *			- search for a line in the static. 
 *				- yes: cut the static variable peer the \n, then return the line.
 *				- no: anything to do.
 */

char	*get_next_line(int fd)
{
	static char	*res_str = 0;
	char		*read_str;
//	char		*line;
	int			bytes_read;

	if (fd == -1)
		return (0);
	bytes_read = 0;
	read_str = read_file(fd, &bytes_read);
	if (!read_str)
		return (0);
	res_str = str_cat(res_str, read_str);
	free(read_str);
	//line = search_line(&res_str, &bytes_read));
	return (res_str);
}

char	*read_file(int fd, int *count)
{
	char	*content;

	content = malloc(sizeof (char) * BUFFER_SIZE + 1);
	if (!content)
		return (0);
	*count = (int) read(fd, content, BUFFER_SIZE);
	content[*count] = 0;
	return (content);
}

char	*str_cat(char *dst, const char *src)
{
	char	*new_dst;
	int		dstlen;
	int		srclen;

	srclen = ft_strlen(src);
	if (!dst)
	{
		new_dst = malloc(sizeof (char) * srclen + 1);
		new_dst = ft_memcpy(new_dst, src, srclen + 1);
	}
	else
	{
		dstlen = ft_strlen(dst);
		new_dst = malloc(sizeof (char) * srclen + dstlen + 1);
		new_dst = ft_memcpy(new_dst, dst, dstlen);
		free(dst);
		new_dst = ft_memcpy(&new_dst[dstlen], src, srclen + 1);
	}
	return (new_dst);
}

char	*search_line(char **str, int *count)
{
	char	*line;
	int		line_len;

	line_len = 0;
	line = 0;
	while ((*str)[line_len] != '\n' && (*str)[line_len] != 0)
		line_len++;
	if (*str || (!*str && *count < BUFFER_SIZE))
	{
		//hay linea recortar el str
		line = ft_memcpy(line, str, line_len + 1);
		//quit_line(*str, line_len + 1);
	}
	else if (*count < BUFFER_SIZE)
	{
		//ultima línea del archivo.
	}
	free(*str);
	*str = NULL;
	return (line);
}
