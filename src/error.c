/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzarza-g <jzarza-g@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 19:15:00 by jzarza-g          #+#    #+#             */
/*   Updated: 2025/06/12 15:11:00 by jzarza-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	error_exit(char *msg)
{
	perror(msg);
	exit(1);
}

void	cleanup_and_exit(char **cmd_args, char *cmd_path, char *msg)
{
	if (cmd_args)
		free_array(cmd_args);
	if (cmd_path)
		free(cmd_path);
	error_exit(msg);
}

void	free_array(char **array)
{
	int	i;

	if (!array)
		return ;
	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}
