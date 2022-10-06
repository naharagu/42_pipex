/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naharagu <naharagu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 19:07:16 by naharagu          #+#    #+#             */
/*   Updated: 2022/10/05 20:54:17 by naharagu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/wait.h>

typedef struct s_info
{
	pid_t	pid1;
	pid_t	pid2;
	int		in;
	int		out;
	char	*path;
	char	**cmd_paths;
	char	**cmd_args;
	char	*cmd;
}			t_info;
