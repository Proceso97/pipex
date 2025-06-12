/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzarza-g <jzarza-g@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 18:40:12 by jzarza-g          #+#    #+#             */
/*   Updated: 2025/06/12 16:17:15 by jzarza-g         ###   ########.fr       */
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

static void	init_pipe(t_pipex *data)
{
	if (pipe(data->pipefd) == -1)
		error_exit("Error creating pipe");
}

static void	first_child_process(t_pipex *data, char **argv)
{
	data->infile = open(argv[1], O_RDONLY);
	if (data->infile == -1)
		error_exit("Error opening input file");
	dup2(data->infile, STDIN_FILENO);
	dup2(data->pipefd[1], STDOUT_FILENO);
	close(data->pipefd[0]);
	close(data->pipefd[1]);
	close(data->infile);
	child_process(data, argv[2]);
}

static void	second_child_process(t_pipex *data, char **argv)
{
	data->outfile = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (data->outfile == -1)
		error_exit("Error opening output file");
	dup2(data->pipefd[0], STDIN_FILENO);
	dup2(data->outfile, STDOUT_FILENO);
	close(data->pipefd[0]);
	close(data->pipefd[1]);
	close(data->outfile);
	child_process(data, argv[3]);
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	data;
	pid_t	pid1;
	pid_t	pid2;
	int		exit_status;

	validate_arguments(argc);
	init_pipe(&data);
	data.envp = envp;
	pid1 = fork();
	if (pid1 == -1)
		error_exit("Error creating first fork");
	if (pid1 == 0)
		first_child_process(&data, argv);
	pid2 = fork();
	if (pid2 == -1)
		error_exit("Error creating second fork");
	if (pid2 == 0)
		second_child_process(&data, argv);
	close(data.pipefd[0]);
	close(data.pipefd[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, &exit_status, 0);
	if (WIFEXITED(exit_status))
		exit_status = WEXITSTATUS(exit_status);
	return (exit_status);
}
