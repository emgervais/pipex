/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egervais <egervais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 13:39:53 by egervais          #+#    #+#             */
/*   Updated: 2023/08/05 14:32:27 by egervais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free2(char **cmd, char *line, t_pipe *pip, char *err)
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
	close(pip->p[0]);
	close(pip->p[1]);
	freee(pip);
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
	if (!pip)
		exit (1);
	if (pip->infile)
		close(pip->infile);
	if (pip->outfile)
		close(pip->outfile);
	if (pip->path)
	{
		while (pip->path[i])
		{
			free(pip->path[i]);
			i++;
		}
		free(pip->path);
	}
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

	pip->cmdtwo = NULL;
	pip->infile = 0;
	pip->outfile = 0;
	path = find_path(envp);
	envp[path] += 5;
	pip->path = ft_split(envp[path], ':');
	pip->infile = open(av[1], O_RDONLY);
	pip->outfile = open(av[ac - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (!pip->path || pip->infile < 0 || pip->outfile < 0)
		return (1);
	return (0);
}
