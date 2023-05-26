/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egervais <egervais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 14:53:59 by egervais          #+#    #+#             */
/*   Updated: 2023/05/26 18:02:47 by egervais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void execute(t_pipe *pip, char *path, char **cmd, char **envp)
{
    if (execve(path, cmd, envp) == -1)
        free_all(pip, 1);
}
int	open_file(char *name, int check, t_pipe *pip)
{
	int	fd;

	if (check == 0)
		fd = open(name, O_RDONLY, 0777);
	else
		fd = open(name, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (fd == -1)
		free_all(pip, 1);
	return (fd);
}

void child_process(t_pipe *pip, int *end, char *name, char **envp)
{
    int fd;
    
    fd = open_file(name, 0, pip);
    if(dup2(fd, 0) == -1 || dup2(end[1], 1) == -1)
        free_all(pip, 1);
    close(end[0]);
    execute(pip, pip->cmdone, pip->cmd1, envp);
}

void parent_process(t_pipe *pip, int *end, char *name, char **envp)
{
    int fd;
    int status;
    
    waitpid(pip->pid, &status, 0);
    fd = open_file(name, 1, pip);
    if(dup2(fd, 1) == -1 || dup2(end[0], 0) == -1)
        free_all(pip, 1);
    close(end[1]);
    execute(pip, pip->cmdtwo, pip->cmd2, envp);
}

int main(int ac, char **av, char **envp)
{
    t_pipe *pip;
    int end[2];
    
    if(ac != 5)
        return (write(2, "Not enought arguments\n", 22), 1);
    if(pipe(end) == -1)
        return (1);
    pip = malloc(sizeof(t_pipe));
    if(!pip)
        return (write(2, "failed to allocate\n", 19), 1);
    pip->cmdtwo = NULL;
    if(init_struct(pip, av, envp) || check_path(pip->path, pip->cmd1, pip, 0) || check_path(pip->path, pip->cmd2, pip, 1))
        free_all(pip, 1);
    pip->pid = fork();
    if(pip->pid == -1)
        return (1);
    if(!pip->pid)
        child_process(pip, end, av[1], envp);
    parent_process(pip, end, av[4], envp);
}