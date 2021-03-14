/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handlers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhakamay <yhakamay@student.42tokyo.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 18:11:56 by yhakamay          #+#    #+#             */
/*   Updated: 2021/03/14 11:37:56 by matsuki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d/cub3d.h"

int no_args_err(void)
{
	printf("Error. No arguments.\n");
	return (0);
}

int no_file_err(void)
{
	printf("Error. No such file.\n");
	return (0);
}
