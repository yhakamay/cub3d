/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhakamay <yhakamay@student.42tokyo.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/11 19:21:44 by yhakamay          #+#    #+#             */
/*   Updated: 2020/10/12 12:29:07 by yhakamay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *buf1, const void *buf2, size_t n)
{
	unsigned char		*dest;
	const unsigned char	*src;

	dest = (unsigned char *)buf1;
	src = (unsigned char *)buf2;
	if (src < dest)
		while (n--)
			*(dest + n) = *(src + n);
	else
		ft_memcpy(buf1, buf2, n);
	return (buf1);
}
