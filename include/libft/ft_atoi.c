/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhakamay <yhakamay@student.42tokyo.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/06 16:57:11 by yhakamay          #+#    #+#             */
/*   Updated: 2020/10/16 20:36:53 by yhakamay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		is_blank(char c)
{
	if ((c >= '\t' && c <= '\r') || c == ' ')
		return (1);
	return (0);
}

static long long	check_overflow(long long n, int sign)
{
	if (errno != ERANGE)
		return (n);
	else if (sign == 1)
		return (-1);
	return (0);
}

int			ft_atoi(const char *s)
{
	int			sign;
	long long	n;

	sign = 1;
	n = 0;
	while (is_blank(*s))
		s++;
	if (*s == '-')
	{
		sign *= -1;
		s++;
	}
	else if (*s == '+')
		s++;
	while (ft_isdigit(*s))
	{
		n *= (n) ? 10 : 1;
		n += *s - '0';
		n = check_overflow(n, sign);
		s++;
	}
	return (n * sign);
}
