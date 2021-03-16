/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matsuki <matsuki@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/18 12:21:18 by matsuki           #+#    #+#             */
/*   Updated: 2021/03/12 14:52:51 by matsuki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdio.h>
# include <stdbool.h>
# include <fcntl.h>
# include "../libft/libft.h"

# define BUFFER_SIZE 32

int		get_next_line(int fd, char **line);

#endif
