/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamerlin <mamerlin@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 17:26:44 by mamerlin          #+#    #+#             */
/*   Updated: 2024/02/06 17:21:41 by mamerlin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

int	ft_search(char *s, char c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			return (i);
		i++;
	}
	return (i);
}

size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	if (!s)
		return (0);
	while (s[len] != '\0')
		len++;
	return (len);
}

char	*ft_substr(char *s, unsigned int start, size_t len, int need_free)
{
	char			*sub;
	size_t			i;

	if (!s)
		return (NULL);
	i = 0;
	if (ft_strlen(s) <= len)
		sub = (char *)malloc(sizeof(char) * ft_strlen(s) + 1);
	else
		sub = (char *)malloc(sizeof(char) * (len + 1));
	if (!sub)
		return (NULL);
	while (start < ft_strlen(s) && i < len)
		sub[i++] = s[start++];
	sub[i] = '\0';
	if (need_free == 1)
		free(s);
	return (sub);
}

char	*ft_strjoin(char *s1, char *s2)
{
	size_t	i;
	size_t	j;
	char	*res;

	i = 0;
	j = 0;
	if (!s1 || !s2)
		return (0);
	res = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!res)
		return (0);
	while (s1[i])
	{
		res[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		res[i + j] = s2[j];
		j++;
	}
	res[i + j] = '\0';
	free(s1);
	return (res);
}

char	*ft_strchr(const char *s, int c)
{
	while ((*s != '\0') && ((char)c != *s))
		s++;
	if ((char)c == *s)
		return ((char *)s);
	return (0);
}
