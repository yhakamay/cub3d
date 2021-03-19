/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handlers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhakamay <yhakamay@student.42tokyo.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 18:11:56 by yhakamay          #+#    #+#             */
/*   Updated: 2021/03/14 12:52:20 by matsuki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d/cub3d.h"

int	no_args_err(void)
{
	printf("Error.\nNo arguments.\n");
	return (0);
}

int	no_file_err(void)
{
	printf("Error.\nNo such file.\n");
	return (0);
}

int	cub_file_err(void)
{
	printf("Error.\n.cub file is not appropriate.\n");
	return (0);
}
