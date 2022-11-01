/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naharagu <naharagu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 23:33:55 by naharagu          #+#    #+#             */
/*   Updated: 2022/11/01 10:13:40 by naharagu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	check_args_and_init(int argc, char **argv, t_info *info)
{
	if (argc != 5)
		put_perror_and_exit("invalid arguments");
	info->fd_in = open(argv[1], O_RDONLY);
	if (info->fd_in < 0)
		put_perror_and_exit("open failed");
	info->fd_out = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, S_IRWXO);
	if (info->fd_out < 0)
		put_perror_and_exit("open failed");
	info->fd_pipe = malloc(sizeof(int) * 2);
	if (!info->fd_pipe)
		put_perror_and_exit("malloc failed");
	if (pipe(info->fd_pipe) < 0)
		put_perror_and_exit("pipe failed");
}

void	put_perror_and_exit(char *s)
{
	perror(s);
	exit(EXIT_FAILURE);
}
