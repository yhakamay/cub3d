/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhakamay <yhakamay@student.42tokyo.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/13 18:17:03 by yhakamay          #+#    #+#             */
/*   Updated: 2020/10/13 20:33:53 by yhakamay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*s_cpy;
	int		i;

	if (!s || !f)
		return (NULL);
	if (!(s_cpy = (char *)malloc(sizeof(char) * (ft_strlen(s) + 1))))
		return (NULL);
	i = -1;
	while (s[++i])
		s_cpy[i] = f(i, s[i]);
	s_cpy[i] = '\0';
	return (s_cpy);
}
