/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzarza-g <jzarza-g@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 19:15:00 by jzarza-g          #+#    #+#             */
/*   Updated: 2025/06/11 21:00:07 by jzarza-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	child_process(t_pipex *data, char *cmd)
{
	char	**cmd_args;
	char	*cmd_path;

	dup2(data->infile, STDIN_FILENO);
	dup2(data->pipefd[1], STDOUT_FILENO);
	close(data->pipefd[0]);
	close(data->pipefd[1]);
	close(data->infile);
	close(data->outfile);
	cmd_args = ft_split(cmd, ' ');
	if (!cmd_args)
		error_exit("Error splitting command");
	cmd_path = find_path(cmd_args[0], data->envp);
	if (!cmd_path)
		cleanup_and_exit(cmd_args, NULL, "Command not found");
	if (execve(cmd_path, cmd_args, data->envp) == -1)
		cleanup_and_exit(cmd_args, cmd_path, "Error executing command");
}

void	parent_process(t_pipex *data, char *cmd)
{
	char	**cmd_args;
	char	*cmd_path;

	dup2(data->pipefd[0], STDIN_FILENO);
	dup2(data->outfile, STDOUT_FILENO);
	close(data->pipefd[0]);
	close(data->pipefd[1]);
	close(data->infile);
	close(data->outfile);
	cmd_args = ft_split(cmd, ' ');
	if (!cmd_args)
		error_exit("Error splitting command");
	cmd_path = find_path(cmd_args[0], data->envp);
	if (!cmd_path)
		cleanup_and_exit(cmd_args, NULL, "Command not found");
	if (execve(cmd_path, cmd_args, data->envp) == -1)
		cleanup_and_exit(cmd_args, cmd_path, "Error executing command");
}
