/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhakamay <yhakamay@student.42tokyo.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/12 14:02:21 by yhakamay          #+#    #+#             */
/*   Updated: 2020/10/16 11:27:21 by yhakamay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	get_len(long n)
{
	size_t	len;

	len = 1;
	if (n < 0)
	{
		len++;
		n *= -1;
	}
	while (n / 10)
	{
		len++;
		n /= 10;
	}
	return (len);
}

char		*ft_itoa(int nb)
{
	char	*s;
	size_t	len;
	long	n;

	n = (long)nb;
	len = get_len(n) - 1;
	if (!(s = (char *)malloc(sizeof(char) * (len + 2))))
		return (NULL);
	s[len + 1] = '\0';
	if (n == 0)
	{
		s[0] = '0';
		return (s);
	}
	if (n < 0)
	{
		s[0] = '-';
		n *= -1;
	}
	while (n)
	{
		s[len--] = n % 10 + '0';
		n /= 10;
	}
	return (s);
}
