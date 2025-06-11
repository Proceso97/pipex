/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzarza-g <jzarza-g@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 19:20:00 by jzarza-g          #+#    #+#             */
/*   Updated: 2025/06/09 19:20:00 by jzarza-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*find_path(char *cmd, char **envp)
{
    char	**paths;
    char	*path;
    char	*part_path;
    int		i;

    i = 0;
    while (envp[i] && ft_strnstr(envp[i], "PATH", 4) == 0)
        i++;
    if (!envp[i])
        return (NULL);
    paths = ft_split(envp[i] + 5, ':');
    i = 0;
    while (paths[i])
    {
        part_path = ft_strjoin(paths[i], "/");
        path = ft_strjoin(part_path, cmd);
        free(part_path);
        if (access(path, F_OK) == 0)
        {
            free_array(paths);
            return (path);
        }
        free(path);
        i++;
    }
    free_array(paths);
    return (NULL);
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