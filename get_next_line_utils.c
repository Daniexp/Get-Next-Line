/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dexposit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 19:29:27 by dexposit          #+#    #+#             */
/*   Updated: 2022/02/24 21:03:31 by dexposit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/*char	*read_file(int fd)
{
	char	*content;
	int		cnt_bytes;

	content = malloc(sizeof (char) * BUFFER_SIZE + 1);
	if (!content)
		return (0);
	cnt_bytes = read(fd, content, BUFFER_SIZE);
	content[cnt_bytes] = 0;
	return (content);
}

char	*cut_line(char *str);
*/
size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (s[len])
		len++;
	return (len);
}

void	*ft_memcpy(void *dest, const void *src, size_t len)
{
	size_t	i;

	if (!dest && !src)
		return (0);
	i = 0;
	while (i < len)
	{
		((char *)dest)[i] = ((char *)src)[i];
		i++;
	}
	return (dest);
}
