/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhakamay <yhakamay@student.42tokyo.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/12 13:44:48 by yhakamay          #+#    #+#             */
/*   Updated: 2020/10/12 20:34:22 by yhakamay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	s_len;
	char	*s_sub;

	if (!s)
		return (NULL);
	s_len = ft_strlen(s);
	if (s_len < start)
	{
		if (!(s_sub = malloc(sizeof(char) * 1)))
			return (NULL);
		s_sub[0] = '\0';
		return (s_sub);
	}
	if (!(s_sub = malloc(sizeof(char) * (len + 1))))
		return (NULL);
	i = 0;
	while (i < len)
	{
		s_sub[i] = s[start + i];
		i++;
	}
	s_sub[i] = '\0';
	return (s_sub);
}
