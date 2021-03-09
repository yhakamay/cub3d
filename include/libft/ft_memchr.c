/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhakamay <yhakamay@student.42tokyo.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/11 19:19:17 by yhakamay          #+#    #+#             */
/*   Updated: 2020/10/12 11:01:30 by yhakamay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *buf, int ch, size_t n)
{
	size_t	i;
	char	*s;

	s = (void *)buf;
	i = -1;
	while (++i < n)
		if (s[i] == (char)ch)
			return (&s[i]);
	return (NULL);
}
