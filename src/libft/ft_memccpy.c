/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhakamay <yhakamay@student.42tokyo.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/11 19:23:04 by yhakamay          #+#    #+#             */
/*   Updated: 2020/10/11 19:23:25 by yhakamay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	size_t			i;
	unsigned char	*cdest;
	unsigned char	*csrc;

	cdest = (unsigned char *)dest;
	csrc = (unsigned char *)src;
	i = 0;
	while (n-- > 0)
	{
		cdest[i] = csrc[i];
		if (csrc[i] == (unsigned char)c)
			return ((void *)(dest + i + 1));
		i++;
	}
	return (NULL);
}
