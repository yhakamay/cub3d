/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhakamay <yhakamay@student.42tokyo.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/12 19:26:38 by yhakamay          #+#    #+#             */
/*   Updated: 2020/10/12 19:48:56 by yhakamay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	unsigned int	un;

	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		un = (unsigned int)(n * -1);
	}
	else
		un = (unsigned int)n;
	if (un > 9)
		ft_putnbr_fd(un / 10, fd);
	ft_putchar_fd((char)(un % 10 + '0'), fd);
}
