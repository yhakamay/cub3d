/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhakamay <yhakamay@student.42tokyo.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/15 00:04:23 by yhakamay          #+#    #+#             */
/*   Updated: 2020/10/15 00:34:40 by yhakamay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list *this;

	if (!lst)
		return ;
	if (!(this = ft_lstlast(*lst)))
	{
		*lst = new;
		return ;
	}
	this->next = new;
	new->next = NULL;
}
