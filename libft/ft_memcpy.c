/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhakamay <yhakamay@student.42tokyo.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/11 19:19:57 by yhakamay          #+#    #+#             */
/*   Updated: 2020/10/11 19:22:43 by yhakamay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *buf1, const void *buf2, size_t n)
{
	size_t			i;
	unsigned char	*dest;
	unsigned char	*src;

	if (buf1 == NULL && buf2 == NULL)
		return (NULL);
	dest = (unsigned char *)buf1;
	src = (unsigned char *)buf2;
	i = 0;
	while (i < n)
	{
		*((char *)dest + i) = *((char *)src + i);
		i++;
	}
	return (dest);
}
