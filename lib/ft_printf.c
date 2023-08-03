/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiniz <ddiniz@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 17:45:58 by ddiniz            #+#    #+#             */
/*   Updated: 2022/06/11 17:22:43 by ddiniz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	converchar_check(char c, va_list args)
{
	if (c == 'c')
		return (print_char(va_arg(args, int)));
	if (c == 's')
		return (print_str(va_arg(args, char *)));
	if (c == 'd' || c == 'i')
		return (print_nbr(va_arg(args, int), SIGNED_INT));
	if (c == 'u')
		return (print_nbr(va_arg(args, unsigned int), UNSIGNED_INT));
	if (c == 'x')
		return (print_hex(va_arg(args, long int), LOWER));
	if (c == 'X')
		return (print_hex(va_arg(args, long int), UPPER));
	if (c == 'p')
		return (print_ptr(va_arg(args, void *)));
	if (c == '%')
		return (print_char('%'));
	return (0);
}

int	ft_printf(const char *str, ...)
{
	va_list	args;
	size_t	index;
	int		len;

	len = 0;
	index = 0;
	if (str == NULL)
		return (-1);
	va_start(args, str);
	while (str[index])
	{
		if (str[index] == '%' && ft_strchr("csdiuxXp%", str[index + 1]))
			len += converchar_check(str[++index], args);
		else
			len += print_char(str[index]);
		index++;
	}
	va_end(args);
	return (len);
}
