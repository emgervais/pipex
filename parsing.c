/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egervais <egervais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 13:39:53 by egervais          #+#    #+#             */
/*   Updated: 2023/07/31 21:51:09 by egervais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free2(char **cmd, char *line, char *err)
{
	int	i;

	i = 0;
	if (cmd)
	{
		while (cmd[i])
		{
			free(cmd[i]);
			i++;
		}
		free(cmd);
	}
	free(line);
	write(2, err, ft_strlen(err));
	exit(1);
}

void	freee(t_pipe *pip)
{
	int	i;

	i = 0;
	if (pip->infile)
		close(pip->infile);
	if (pip->outfile)
		close(pip->outfile);
	while (pip->path[i])
	{
		free(pip->path[i]);
		i++;
	}
	free(pip->path);
	free(pip);
}

void	freee2(t_pipe *pip)
{
	int	i;

	i = 0;
	if (pip->infile)
		close(pip->infile);
	if (pip->outfile)
		close(pip->outfile);
	while (pip->path[i])
	{
		free(pip->path[i]);
		i++;
	}
	free(pip->path);
	free(pip);
	exit (1);
}

static int	find_path(char **env)
{
	int	i;

	i = 0;
	while (!ft_strstr(env[i], "PATH="))
		i++;
	return (i);
}

int	init_struct(t_pipe *pip, char **av, char **envp, int ac)
{
	int	path;

	pip->infile = 0;
	pip->outfile = 0;
	path = find_path(envp);
	envp[path] += 5;
	pip->path = ft_split(envp[path], ':');
	pip->infile = open(av[1], O_RDONLY);
	pip->outfile = open(av[ac - 1], O_TRUNC | O_CREAT | O_RDWR, 0000644);
	if (!pip->path || pip->infile < 0 || pip->outfile < 0)
		return (1);
	return (0);
}
