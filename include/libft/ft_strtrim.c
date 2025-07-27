/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamerlin <mamerlin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 11:41:18 by mamerlin          #+#    #+#             */
/*   Updated: 2024/01/15 11:48:44 by mamerlin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

bool	ft_find(char const c, char const *set)
{
	int	i;

	i = 0;
	while (set[i] != '\0')
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

int	ft_insert(char *s1, char *str, int start, int end)
{
	int	i;

	i = 0;
	while (i < end)
	{
		str[i] = s1[start];
		i++;
		start++;
	}
	str[i] = '\0';
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	if (!s1 || !set)
		return (NULL);
	j = ft_strlen(s1) - 1;
	while (s1[i] != '\0' && (ft_find(s1[i], set)))
		i++;
	while ((ft_find(s1[j], set)) && j > i)
		j--;
	str = (char *)malloc(sizeof(char) * (j - i + 2));
	if (!str)
		return (NULL);
	ft_insert((char *) s1, str, i, (j - i + 1));
	return (str);
}
