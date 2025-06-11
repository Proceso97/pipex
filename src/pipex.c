/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzarza-g <jzarza-g@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 18:40:12 by jzarza-g          #+#    #+#             */
/*   Updated: 2025/06/11 21:11:31 by jzarza-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	validate_arguments(int argc)
{
	if (argc != 5)
	{
		write(2, "Error: Usage: ./pipex infile cmd1 cmd2 outfile\n", 48);
		exit(1);
	}
}

static void	init_files(t_pipex *data, char **argv)
{
	data->infile = open(argv[1], O_RDONLY);
	if (data->infile == -1)
		error_exit("Error opening input file");
	data->outfile = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (data->outfile == -1)
	{
		close(data->infile);
		error_exit("Error opening output file");
	}
}

static void	init_pipe(t_pipex *data)
{
	if (pipe(data->pipefd) == -1)
		error_exit("Error creating pipe");
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	data;
	pid_t	pid;

	validate_arguments(argc);
	init_files(&data, argv);
	init_pipe(&data);
	data.envp = envp;
	pid = fork();
	if (pid == -1)
		error_exit("Error creating fork");
	if (pid == 0)
	{
		child_process(&data, argv[2]);
	}
	else
	{
		wait(NULL);
		parent_process(&data, argv[3]);
	}
	return (0);
}
