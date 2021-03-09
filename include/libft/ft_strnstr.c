/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhakamay <yhakamay@student.42tokyo.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/12 12:28:05 by yhakamay          #+#    #+#             */
/*   Updated: 2020/10/15 11:58:00 by yhakamay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	n;
	size_t	len_needle;

	if (*needle == '\0')
		return ((char *)haystack);
	n = 0;
	len_needle = ft_strlen(needle);
	while (*haystack != '\0')
	{
		if (n + len_needle > len)
			return (NULL);
		if (ft_strncmp(haystack, needle, len_needle) == 0)
			return (char *)haystack;
		haystack++;
		n++;
	}
	return (NULL);
}
