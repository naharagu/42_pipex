/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naharagu <naharagu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 19:02:09 by naharagu          #+#    #+#             */
/*   Updated: 2022/10/31 16:00:13 by naharagu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*get_cmdpath(char *cmd, char **envp)
{
	char	**paths;
	char	*tmp;
	char	*full_path_cmd;

	while (ft_strncmp("PATH=", *envp, 5))
		envp++;
	paths = ft_split(&envp[0][5], ':');
	printf("paths = :%s", paths[0]);
	if (!paths)
		put_perror_and_exit("Error: ft_split");
	while (*paths)
	{
		tmp = ft_strjoin(*paths, "/");
		if (tmp == NULL)
			put_perror_and_exit("strjoin error");
		full_path_cmd = ft_strjoin(tmp, cmd);
		if (full_path_cmd == NULL)
			put_perror_and_exit("strjoin error");
		free(tmp);
		if (access(full_path_cmd, 0) == 0)
			return (full_path_cmd);
		free(full_path_cmd);
		paths++;
	}
	return (NULL);
}

void	execute_child_process(char **argv, char **envp, t_info *info)
{
	char	**cmd_arg;
	char	*cmd_path;

	close(info->fd_pipe[0]);
	if (dup2(info->fd_pipe[1], STDOUT_FILENO) == -1)
		put_perror_and_exit("dup2");
	close(info->fd_pipe[1]);
	if (dup2(info->fd_in, STDIN_FILENO) == -1)
		put_perror_and_exit("dup2");
	cmd_arg = ft_split(argv[2], ' ');
	if (!cmd_arg)
		put_perror_and_exit("split");
	cmd_path = get_cmdpath(cmd_arg[0], envp);
	// ft_putstr_fd(cmd_path, 2);
	if (!cmd_path)
		put_perror_and_exit("cmd not found");
	if (execve(cmd_path, cmd_arg, envp) == -1)
		put_perror_and_exit("execve");
}

void	execute_parent_process(char **argv, char **envp, t_info *info,
		pid_t *pid)
{
	char	**cmd_arg;
	char	*cmd_path;

	waitpid(*pid, &info->pid_status, WNOHANG);
	close(info->fd_pipe[1]);
	if (dup2(info->fd_pipe[0], STDIN_FILENO) == -1)
		put_perror_and_exit("dup2");
	close(info->fd_pipe[0]);
	if (dup2(info->fd_out, STDOUT_FILENO) == -1)
		put_perror_and_exit("dup2");
	cmd_arg = ft_split(argv[3], ' ');
	if (!cmd_arg)
		put_perror_and_exit("split");
	cmd_path = get_cmdpath(cmd_arg[0], envp);
	// ft_putstr_fd(cmd_path, 2);
	if (!cmd_path)
		put_perror_and_exit("cmd not found");
	if (execve(cmd_path, cmd_arg, envp) == -1)
		put_perror_and_exit("execve");
}

void	pipex(char **argv, char **envp, t_info *info)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		put_perror_and_exit("fork");
	else if (pid == 0)
		execute_child_process(argv, envp, info);
	else if (pid > 0)
		execute_parent_process(argv, envp, info, &pid);
}

int	main(int argc, char **argv, char **envp)
{
	t_info	info;

	check_args_and_init(argc, argv, &info);
	pipex(argv, envp, &info);
	if (waitpid(-1, NULL, 0) == -1)
		put_perror_and_exit("wait");
	return (EXIT_SUCCESS);
}
