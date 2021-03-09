/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhakamay <yhakamay@student.42tokyo.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/06 16:43:15 by yhakamay          #+#    #+#             */
/*   Updated: 2020/10/16 14:41:24 by yhakamay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t dest_size)
{
	size_t	i;

	if (!dest || !src)
		return (0);
	i = 0;
	if (dest_size == 0)
	{
		while (src[i])
			i++;
		return (i);
	}
	while (src[i] && i < dest_size - 1)
	{
		dest[i] = src[i];
		i++;
	}
	if (i < dest_size)
		dest[i] = '\0';
	while (src[i])
		i++;
	return (i);
}
