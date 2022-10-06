/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naharagu <naharagu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 19:02:09 by naharagu          #+#    #+#             */
/*   Updated: 2022/10/05 21:12:12 by naharagu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	execute_first_cmd(int *fd, char **argv, char **envp)
{
	int	fd_in;

	fd_in = open(argv[1], O_RDONLY);
	
}

int main(int argc, char ** argv, char ** envp)
{
	int		fd[2];
	pid_t	pid1;
	pid_t	pid2;


	if (argc != 5)
		return ;
	pid1 = fork();
	execute_first_cmd(fd, argv, envp);

	pid2 = fork();
	execute_second_cmd(fd, argv, envp);

	close(fd[0]);
	close(fd[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
}
