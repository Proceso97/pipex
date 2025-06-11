/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzarza-g <jzarza-g@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 18:29:57 by jzarza-g          #+#    #+#             */
/*   Updated: 2025/06/09 18:51:50 by jzarza-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <fcntl.h>
# include <stdlib.h>
# include <string.h>
# include <stdio.h>
# include "../libft/libft.h"

typedef struct s_pipex
{
	int		infile;
	int		outfile;
	int		pipefd[2];
	char	**envp;
}	t_pipex;

/* Funciones principales */
void	error_exit(char *msg);
void	child_process(t_pipex *data, char *cmd);
void	parent_process(t_pipex *data, char *cmd);
char	*find_path(char *cmd, char **envp);
void	free_array(char **array);

#endif

