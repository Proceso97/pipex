/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzarza-g <jzarza-g@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 19:15:00 by jzarza-g          #+#    #+#             */
/*   Updated: 2025/06/12 15:57:26 by jzarza-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	child_process(t_pipex *data, char *cmd)
{
	char	**cmd_args;
	char	*cmd_path;

	cmd_args = ft_split(cmd, ' ');
	if (!cmd_args)
		error_exit("Error splitting command");
	cmd_path = find_path(cmd_args[0], data->envp);
	if (!cmd_path)
		cleanup_and_exit(cmd_args, NULL, "Command not found");
	if (execve(cmd_path, cmd_args, data->envp) == -1)
		cleanup_and_exit(cmd_args, cmd_path, "Error executing command");
}
