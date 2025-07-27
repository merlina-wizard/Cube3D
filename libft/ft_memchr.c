/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamerlin <mamerlin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 12:34:32 by mamerlin          #+#    #+#             */
/*   Updated: 2024/01/11 10:49:00 by mamerlin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*ptr;

	ptr = (unsigned char *)s;
	i = 0;
	while (*ptr != '\0' && (unsigned char)c != *ptr && i < n)
	{
		i++;
		ptr++;
	}
	if ((unsigned char)c == *ptr && i < n)
		return ((void *)ptr);
	return (NULL);
}
