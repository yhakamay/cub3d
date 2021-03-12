/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matsuki <matsuki@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/17 16:44:05 by matsuki           #+#    #+#             */
/*   Updated: 2021/03/12 14:51:31 by matsuki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		safe_free(char **p)
{
	free(*p);
	*p = NULL;
	return (-1);
}

int		check_new_line(char **line, char **save)
{
	int		i;
	char	*temp;

	i = 0;
	while ((*save)[i] != '\0')
	{
		if ((*save)[i] == '\n')
		{
			if (!(*line = malloc(sizeof(char) * (i + 1))))
				return (safe_free(save));
			ft_strlcpy(*line, *save, i + 1);
			if (!(temp = ft_strdup(*save + i + 1)))
				return (safe_free(save));
			safe_free(save);
			*save = temp;
			return (0);
		}
		i++;
	}
	return (1);
}

ssize_t	read_file(int fd, char **save)
{
	char	*buf;
	char	*temp;
	ssize_t	ret;

	if (!(buf = malloc(sizeof(char) * BUFFER_SIZE + 1)))
		return (safe_free(save));
	ret = read(fd, buf, BUFFER_SIZE);
	if (ret == 0 || ret == -1)
	{
		safe_free(&buf);
		return (ret);
	}
	buf[ret] = '\0';
	if (!(temp = ft_strjoin(*save, buf)))
	{
		safe_free(&buf);
		safe_free(save);
		return (-1);
	}
	safe_free(save);
	safe_free(&buf);
	*save = temp;
	return (ret);
}

int		get_next_line(int fd, char **line)
{
	static char	*save;
	int			flag;
	ssize_t		ret;

	if (line == NULL || fd < 0 || BUFFER_SIZE <= 0)
		return (safe_free(&save));
	if (save == 0)
		if (!(save = ft_strdup("")))
			return (-1);
	ret = 1;
	while (ret != 0 && (flag = check_new_line(line, &save)))
	{
		ret = read_file(fd, &save);
		if (ret == -1 || flag == -1)
			return (-1);
	}
	if (ret == 0 && flag == 1)
	{
		if (!(*line = ft_strdup(save)))
			return (safe_free(&save));
		safe_free(&save);
		return (0);
	}
	return (1);
}
