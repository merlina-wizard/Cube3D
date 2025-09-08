/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamerlin <mamerlin@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 17:13:42 by mamerlin          #+#    #+#             */
/*   Updated: 2024/02/06 17:21:33 by mamerlin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_strdup(const char *src)
{
	int		i;
	char	*dst;

	i = 0;
	while (src[i] != '\0')
		i++;
	dst = (char *)malloc(sizeof(char) * (i + 1));
	if (!dst)
		return (NULL);
	i = 0;
	while (src[i] != '\0')
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

static char	*ft_read(int fd, char *save)
{
	char	*temp;
	int		i;

	temp = (char *)malloc(sizeof(char) * BUFFER_SIZE + 1);
	while (!ft_strchr(save, '\n'))
	{
		i = read (fd, temp, BUFFER_SIZE);
		if (i == 0 || i == -1)
			break ;
		temp[i] = '\0';
		save = ft_strjoin(save, temp);
	}
	free (temp);
	if (ft_strlen(save) == 0)
	{
		free(save);
		return (NULL);
	}
	return (save);
}

char	*get_next_line(int fd)
{
	static char	*save[257];
	char		*ret_n;

	if (fd < 0 || fd > 256 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!save[fd])
		save[fd] = ft_strdup("");
	save[fd] = ft_read(fd, save[fd]);
	if (!save[fd])
		return (NULL);
	ret_n = ft_substr(save[fd], 0, ft_search(save[fd], '\n') + 1, 0);
	save[fd] = ft_substr(save[fd], ft_search(save[fd], '\n') + 1,
			ft_strlen(save[fd]), 1);
	return (ret_n);
}
