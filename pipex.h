/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egervais <egervais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 14:54:47 by egervais          #+#    #+#             */
/*   Updated: 2023/05/26 17:59:57 by egervais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
#define PIPEX_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>


typedef struct s_pipe
{
    char **path;
    char **cmd1;
    char **cmd2;
    char *cmdone;
    char *cmdtwo;
    pid_t pid;
} t_pipe;

char	*ft_strjoin(char *s1, char *s2);
char	*ft_strstr(char *str, char *to_find);
char	**ft_split(char const *s, char c, int mode);
int	ft_strlen(const char *str);
int check_path(char **paths, char **cmd, t_pipe *pip, int check);
void free_all(t_pipe *pip, int check);
int init_struct(t_pipe *pip, char **av, char **envp);

#endif