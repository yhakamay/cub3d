/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhakamay <yhakamay@student.42tokyo.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/12 12:28:25 by yhakamay          #+#    #+#             */
/*   Updated: 2020/10/12 12:28:27 by yhakamay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *buf1, const void *buf2, size_t n)
{
	const unsigned char	*s1;
	const unsigned char	*s2;

	if (buf1 == buf2 || n == 0)
		return (0);
	s1 = (const unsigned char *)buf1;
	s2 = (const unsigned char *)buf2;
	while (n--)
	{
		if (*s1 != *s2)
			return (*s1 - *s2);
		s1++;
		s2++;
	}
	return (0);
}
