/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naharagu <naharagu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 19:02:09 by naharagu          #+#    #+#             */
/*   Updated: 2022/10/24 23:29:07 by naharagu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	put_perror_and_exit(char *s)
{
	perror(s);
	exit(EXIT_FAILURE);
}

char	*get_cmdpath(char **envp, char *cmd)
{
	char	**paths;
	char	*tmp;
	char	*full_path_cmd;

	while (ft_strncmp("PATH=", *envp, 5))
		envp++;
	paths = ft_split(&envp[0][5], ':');
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

void	set_dup2(t_data *data, size_t i)
{
	if (!i)
	{
		if (dup2(data->fd_in, STDIN_FILENO) == -1)
			put_perror_and_exit("dup2");
		if (dup2(data->fd_pipe[1], STDOUT_FILENO) == -1)
			put_perror_and_exit("dup2");
	}
	else
	{
		if (dup2(data->fd_in, STDOUT_FILENO) == -1)
			put_perror_and_exit("dup2");
		if (dup2(data->fd_pipe[0], STDIN_FILENO) == -1)
			put_perror_and_exit("dup2");
	}
}

void	execute_cmd(char **argv, char **envp, t_data *data, size_t i)
{
	pid_t	pid;
	char	*cmd_path;

	pid = fork();
	if (pid == -1)
		put_perror_and_exit("fork");
	set_dup2(data, i);
	close(data->fd_in);
	close(data->fd_pipe[0]);
	close(data->fd_pipe[1]);
	cmd_path = get_cmdpath(envp, argv[2]);
	if (execve(cmd_path, argv, envp) == -1)
		put_perror_and_exit("execve");
}

void	check_args_and_init(int argc, char **argv, t_data *data)
{
	if (argc != 5)
		put_perror_and_exit("invalid arguments");
	data->fd_in = open(argv[1], O_RDONLY);
	if (data->fd_in < 0)
		put_perror_and_exit("open");
	data->fd_out = open(argv[4], O_CREAT | O_WRONLY | O_TRUNC, 0777);
	if (data->fd_out < 0)
		put_perror_and_exit("open");
	pipe(data->fd_pipe);
	if (data->fd_pipe < 0)
		put_perror_and_exit("pipe");
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;
	size_t	i;

	i = 0;
	check_args_and_init(argc, argv, &data);
	execute_cmd(argv, envp, &data, i);
	exit(EXIT_SUCCESS);
}
