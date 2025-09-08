/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamerlin <mamerlin@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 15:19:46 by mamerlin          #+#    #+#             */
/*   Updated: 2024/02/06 17:22:11 by mamerlin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <stdarg.h>
# include <stdio.h>
# include <stdint.h>
# include <limits.h>
# include <fcntl.h>

# ifndef BUFFER_SIZE

# endif

char		*get_next_line(int fd);
char		*ft_strdup(const char *src);
char		*ft_strjoin(char *s1, char *s2);
int			ft_search(char *s, char c);
size_t		ft_strlen(const char *s);
char		*ft_substr(char *s, unsigned int start, size_t len, int need_free);
char		*ft_strchr(const char *s, int c);

#endif
