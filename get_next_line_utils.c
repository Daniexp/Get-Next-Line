/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dexposit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 19:29:27 by dexposit          #+#    #+#             */
/*   Updated: 2022/02/25 22:31:38 by dexposit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (s[len])
		len++;
	return (len);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*subs;
	size_t	i;
	size_t	j;

	if (!s)
		return (0);
	if (len > ft_strlen(s) - start)
		len = ft_strlen(s) - start;
	if (start > ft_strlen(s))
		len = 0;
	subs = (char *)malloc(len + 1);
	if (!subs)
		return (0);
	i = start;
	j = 0;
	while (j < len)
	{
		subs[j++] = s[i++];
	}
	subs[j] = '\0';
	return (subs);
}

char	*ft_strrchr(const char *s, int c)
{
	char	*ptr;
	if (!s)
		return (NULL);
	ptr = 0;
	while (*s)
	{
		if (*s == (unsigned char)c)
			ptr = (char *)s;
		s++;
	}
	if (c == 0)
		ptr = (char *)s;
	return (ptr);
}

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*aux;

	aux = s;
	while (n > 0)
	{
		*aux = '\0';
		n--;
		aux++;
	}
	return ;
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
