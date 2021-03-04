/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhakamay <yhakamay@student.42tokyo.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/12 12:28:47 by yhakamay          #+#    #+#             */
/*   Updated: 2020/10/12 12:28:49 by yhakamay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	len;

	len = ft_strlen(s);
	if ((char)c == '\0')
		return ((char *)s + len);
	while (len--)
		if (s[len] == c)
			return ((char *)(s + len));
	return (NULL);
}
