/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bede-car <bede-car@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 16:13:44 by ddiniz            #+#    #+#             */
/*   Updated: 2023/09/06 12:43:46 by bede-car         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *str, int c)
{
	if (!*str) 
		return (NULL);
	while (*str || *str != c)
	{
		str++;
		if (*str == c)
			return ((char *)str);
	}
	return (NULL);
}
