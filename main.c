/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egervais <egervais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 14:53:59 by egervais          #+#    #+#             */
/*   Updated: 2023/07/31 21:51:15 by egervais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	*command(char **path, char *cmd)
{
	char	*temp;
	char	*com;

	if (!cmd)
		return (NULL);
	while (*path)
	{
		temp = ft_strjoin(*path, "/");
		com = ft_strjoin(temp, cmd);
		free(temp);
		if (!com)
			return (NULL);
		if (access(com, 0) == 0)
			return (com);
		free(com);
		path++;
	}
	return (NULL);
}

static void	child(t_pipe *pip, char **envp, char **av)
{
	if (dup2(pip->p[1], 1) < 0)
		exit(1);
	close(pip->p[0]);
	if (dup2(pip->infile, 0) < 0)
		exit(1);
	pip->cmd1 = ft_split(av[2], ' ');
	pip->cmdone = command(pip->path, *pip->cmd1);
	if (!pip->cmdone)
		free2(pip->cmd1, pip->cmdone, "invalid command\n");
	if (execve(pip->cmdone, pip->cmd1, envp) == -1)
		free2(pip->cmd1, pip->cmdone, "execution failed\n");
}

static void	parent(t_pipe *pip, char **envp, char **av)
{
	if (dup2(pip->p[0], 0) < 0)
		exit(1);
	close(pip->p[1]);
	if (dup2(pip->outfile, 1) < 0)
		exit(1);
	pip->cmd2 = ft_split(av[3], ' ');
	pip->cmdtwo = command(pip->path, *pip->cmd2);
	if (!pip->cmdtwo)
		free2(pip->cmd2, pip->cmdtwo, "invalid command\n");
	if (execve(pip->cmdtwo, pip->cmd2, envp) == -1)
		free2(pip->cmd2, pip->cmdtwo, "execution failed\n");
}

int	main(int ac, char **av, char **envp)
{
	t_pipe	*pip;

	if (ac != 5)
		return (write(2, "Not enought arguments\n", 22), 1);
	pip = malloc(sizeof(t_pipe));
	if (!pip)
		return (write(2, "failed to allocate\n", 19), 1);
	pip->cmdtwo = NULL;
	if (init_struct(pip, av, envp, ac) || pipe(pip->p) == -1)
		freee2(pip);
	pip->pid = fork();
	if (pip->pid == -1)
		freee(pip);
	if (!pip->pid)
		child(pip, envp, av);
	pip->pid2 = fork();
	if (!pip->pid2)
		parent(pip, envp, av);
	close(pip->p[0]);
	close(pip->p[1]);
	waitpid(pip->pid, NULL, 0);
	waitpid(pip->pid2, NULL, 0);
	freee(pip);
}
