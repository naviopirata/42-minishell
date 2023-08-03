
#include "libft.h"

size_t	ft_strlcpygnl(char *dst, const char *src, size_t size)
{
	size_t	len_src;

	len_src = ft_strlen(src);
	if (size--)
	{
		while (size-- && *src)
			*dst++ = *src++;
		*dst = '\0';
	}
	return (len_src);
}
