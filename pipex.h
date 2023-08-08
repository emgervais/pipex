/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egervais <egervais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 14:54:47 by egervais          #+#    #+#             */
/*   Updated: 2023/08/05 14:11:01 by egervais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_pipe
{
	char	**path;
	char	**cmd1;
	char	**cmd2;
	char	*cmdone;
	char	*cmdtwo;
	int		infile;
	int		outfile;
	int		p[2];
	pid_t	pid;
	pid_t	pid2;
}			t_pipe;

char		*ft_strjoin(char *s1, char *s2);
char		*ft_strstr(char *str, char *to_find);
char		**ft_split(char const *s, char c);
char		*ft_substr(char const *s, unsigned int start, size_t len);
int			ft_strlen(const char *str);
int			check_path(char **paths, char **cmd, t_pipe *pip, int check);
void		freee(t_pipe *pip);
void		freee2(t_pipe *pip);
void		free2(char **cmd, char *line, t_pipe *pip, char *err);
int			init_struct(t_pipe *pip, char **av, char **envp, int ac);

#endif