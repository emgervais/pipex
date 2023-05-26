/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egervais <egervais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 13:39:53 by egervais          #+#    #+#             */
/*   Updated: 2023/05/26 18:02:25 by egervais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void free_all(t_pipe *pip, int check)
{
    int i;

    i = 0;
    if(pip->cmd1)
        while(pip->cmd1[i])
            free(pip->cmd1[i++]);
    free(pip->cmd1);
    i = 0;
    if(pip->cmd2)
        while(pip->cmd2[i])
            free(pip->cmd2[i++]);
    free(pip->cmd2);
    i = 0;
    if(pip->path)
        while(pip->path[i])
            free(pip->path[i++]);
    free(pip->path);
    if(pip->cmdtwo)
    {
    free(pip->cmdone);
    free(pip->cmdtwo);
    }
    free(pip);
    if(check)
    {
        write(2, "./pipex infile cmd cmd outfile\n", 31);
        exit(EXIT_FAILURE);
    }
    exit(0);
}

static int find_path(char **env)
{
    int i;

    i = 0;
    while(!ft_strstr(env[i], "PATH="))
        i++;
    return(i);
}

int check_path(char **paths, char **cmd, t_pipe *pip, int check)
{
    int i;
    char *path;

    i = 0;
    while(paths[i])
    {
        path = ft_strjoin(paths[i++], cmd[0]);
        if(!path)
            return (1);
        if(!access(path, F_OK | X_OK))
        {
            if(!check)
                pip->cmdone = path;
            else
                pip->cmdtwo = path;
            return (0);
        }
        free(path);
    }
    return(1);
}

int init_struct(t_pipe *pip, char **av, char **envp)
{
    int path;
    
    path = find_path(envp);
    envp[path] += 5;
    pip->path = ft_split(envp[path], ':', 0);
    pip->cmd1 = ft_split(av[2], ' ', 1);
    pip->cmd2 = ft_split(av[3], ' ', 1);
    if(!pip->path || !pip->cmd1 || !pip->cmd2)
        return (1);
    return (0);
}