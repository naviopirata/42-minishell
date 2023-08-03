/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiniz <ddiniz@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 20:34:58 by ddiniz            #+#    #+#             */
/*   Updated: 2023/05/21 13:05:38 by ddiniz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	char	*save_dst;
	size_t	len_src;

	save_dst = dst;
	len_src = ft_strlen(src);
	if (size--)
	{
		while (size-- && *src)
			*dst++ = *src++;
		*dst = '\0';
	}
	dst = save_dst;
	// gnl dont use save_dst?
	return (len_src);
}
