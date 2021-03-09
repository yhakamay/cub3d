/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhakamay <yhakamay@student.42tokyo.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/16 17:54:17 by yhakamay          #+#    #+#             */
/*   Updated: 2020/10/16 20:28:22 by yhakamay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_strs(char const *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 1;
	while (s[i] == c)
		i++;
	while (s[i] != '\0')
	{
		while (s[i] != c && s[i] != '\0')
			i++;
		count++;
		if (s[i] != '\0')
			while (s[i] == c)
				i++;
	}
	return (count);
}

static char	*get_next_part(char *part, char c, int *len_part)
{
	int	i;

	if (*part != '\0')
		while (*part == c)
			part++;
	i = 0;
	while (part[i] != c && part[i] != '\0')
		i++;
	*len_part = i;
	return (part);
}

static void	free_strs(char **ret, int count_strs)
{
	int	i;

	i = 0;
	while (i <= count_strs)
		free(ret[i++]);
	free(ret);
}

char		**ft_split(char const *s, char c)
{
	char	**ret;
	char	*part;
	int		i;
	int		len_part;

	if (!(ret = (char **)malloc(sizeof(char *) * count_strs(s, c) + 1)))
		return (NULL);
	i = 0;
	part = get_next_part((char *)s, c, &len_part);
	while (*part)
	{
		if (!(ret[i] = (char *)malloc(sizeof(char) * (len_part + 1))))
		{
			free_strs(ret, i);
			return (NULL);
		}
		ft_strlcpy(ret[i], part, len_part + 1);
		part = get_next_part(part + len_part, c, &len_part);
		i++;
	}
	ret[i] = NULL;
	return (ret);
}
