/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiniz <ddiniz@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 21:42:25 by ddiniz            #+#    #+#             */
/*   Updated: 2022/05/13 21:48:00 by ddiniz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	line_update(char **line, const char *buffer, size_t size)
{
	char	*aux;
	size_t	len_line;

	aux = NULL;
	if (buffer[0])
	{
		len_line = ft_strlen(*line);
		aux = (char *)malloc((len_line + size + 1) * sizeof(char));
		if (aux != NULL)
		{
			ft_strlcpygnl(aux, *line, len_line + 1);
			ft_strlcpygnl(aux + len_line, buffer, size + 1);
		}
	}
	free(*line);
	*line = aux;
}

char	*line_getnext(int fd)
{
	static char	buff[BUFFER_SIZE + 1];
	char		*line;
	char		*aux;
	ssize_t		n_read;

	line = NULL;
	n_read = -1;
	while (!ft_strchr(line, '\n') && n_read != 0)
	{
		aux = ft_strchr(buff, '\n');
		if (aux++)
		{
			line_update(&line, buff, aux - buff);
			ft_strlcpygnl(buff, aux, ft_strlen(aux) + 1);
			continue ;
		}
		line_update(&line, buff, ft_strlen(buff));
		n_read = read(fd, buff, BUFFER_SIZE);
		if (n_read < 0)
			return (NULL);
		buff[n_read] = '\0';
	}
	return (line);
}
