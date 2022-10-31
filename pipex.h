/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naharagu <naharagu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 19:07:16 by naharagu          #+#    #+#             */
/*   Updated: 2022/10/31 15:59:05 by naharagu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft/libft.h"
# include <fcntl.h>
# include <stdio.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct s_info
{
	int		fd_in;
	int		fd_out;
	int		*fd_pipe;
	int		pid_status;
	char	*path;
	char	**cmd_arg;
}			t_info;

void		check_args_and_init(int argc, char **argv, t_info *info);
char		*get_cmdpath(char *cmd, char **envp);
void		execute_child_process(char **argv, char **envp, t_info *info);
void		execute_parent_process(char **argv, char **envp, t_info *info,
				pid_t *pid);
void		pipex(char **argv, char **envp, t_info *info);
void		put_perror_and_exit(char *s);

#endif