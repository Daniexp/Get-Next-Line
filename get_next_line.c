/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dexposit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 19:29:14 by dexposit          #+#    #+#             */
/*   Updated: 2022/02/25 22:31:44 by dexposit         ###   ########.fr       */
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

//	printf("aux_str: %s\nread_str: %s\n ", first, end);
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
		ft_memcpy(res + ft_strlen(first) + 1, end, ft_strlen(end));
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
	

	aux_str = 0;
	result = 0;
	//poner en aux_str rest_read
	if (rest_read)
		aux_str = ft_substr(rest_read, 0, ft_strlen(rest_read));
	if (aux_str)
	{
	//limpiar rest_read
		//ft_bzero(rest_read, BUFFER_SIZE);
		free(rest_read);
		rest_read = NULL;
	//comprobar aux_str si tiene \n
		if (ft_strrchr(aux_str, '\n'))
			{
	//	la línea va a result
				result = ft_substr(aux_str, 0, ft_strrchr(aux_str, '\n') - aux_str + 1);
				if (!result)
					return (0);
	//		sobrante a rest_read
				ft_memcpy(rest_read, ft_strrchr(aux_str, '\n') + 1, ft_strlen(ft_strrchr(aux_str, '\n') + 1));
				free(aux_str);
			}
	}
	//si no hay que leer para saber si hay mas líneas o es final del archivo.
	while (!result)
	{
		//crear read_str y saber si final o no del archivo
		read_str = malloc(BUFFER_SIZE * sizeof(char) + 1);
		if (!read_str)
			return (0);
		cnt_bytes = read(fd, read_str, BUFFER_SIZE);
		if (cnt_bytes <= 0)
			break;
		//read_str[BUFFER_SIZE] = '\0';
		read_str[cnt_bytes] = '\0';
		//printf("\n%s\n", read_str);
		if (cnt_bytes >= 0)
		//unir aux_str con read_str luego liberar read_str	
			aux_str = cat(aux_str, read_str);
		//printf("\n%s\n", aux_str);
		//buscar linea en aux_str o final de archivo
		//si hay linea la pasamos a result y el exceso lo ponemos en la static char
			if (ft_strrchr(aux_str, '\n'))
			{
	//	la línea va a result
				result = ft_substr(aux_str, 0, ft_strrchr(aux_str, '\n') - aux_str + 1);
				//printf("\n%s\n", result);
				if (!result)
					return (0);
	//		sobrante a rest_read
				rest_read = ft_substr(ft_strrchr(aux_str, '\n') + 1, 0, ft_strlen(ft_strrchr(aux_str, '\n') + 1));
				//ft_memcpy(rest_read, ft_strrchr(aux_str, '\n') + 1, ft_strlen(ft_strrchr(aux_str, '\n') + 1));
				free(aux_str);
			}
		//si final de archivo lo pasamos todo a result y listo
			else if (cnt_bytes < BUFFER_SIZE && cnt_bytes > 0)
		{
			result = ft_substr(aux_str, 0, ft_strlen(aux_str));
			free(aux_str);
			free(rest_read);
			rest_read = NULL;
		}
		//si no hay linea ni final del archivo volveremos a leer.
		free(read_str);
	}
	//llegamos cuando tenemos un resulado es decir tener una linea o el final del archivo
	//printf("\n");
	return (result);
}
