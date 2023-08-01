/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egervais <egervais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 17:51:58 by egervais          #+#    #+#             */
/*   Updated: 2023/07/17 22:00:07 by egervais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	ft_count_word(char const *s, char c)
{
	int	i;
	int	word;

	i = 0;
	word = 0;
	while (s && s[i])
	{
		if (s[i] != c)
		{
			word++;
			while (s[i] != c && s[i])
				i++;
		}
		else
			i++;
	}
	return (word);
}

static int	ft_size_word(char const *s, char c, int i)
{
	int	size;

	size = 0;
	while (s[i] != c && s[i])
	{
		size++;
		i++;
	}
	return (size);
}

static void	ft_free(char **strs, int j)
{
	while (j-- > 0)
		free(strs[j]);
	free(strs);
}

static char	**filltab(char **tab, char const *s, char c)
{
	int	i;
	int	word;
	int	size;
	int	j;

	i = 0;
	j = -1;
	word = ft_count_word(s, c);
	while (++j < word)
	{
		while (s[i] == c)
			i++;
		size = ft_size_word(s, c, i);
		tab[j] = ft_substr(s, i, size);
		if (!tab[j])
		{
			ft_free(tab, j);
			return (NULL);
		}
		i += size;
	}
	tab[j] = 0;
	return (tab);
}

char	**ft_split(char const *s, char c)
{
	int		word;
	char	**tab;

	if (!s)
		return (NULL);
	word = ft_count_word(s, c);
	tab = (char **)malloc((word + 1) * sizeof(char *));
	if (!tab)
		return (NULL);
	tab = filltab(tab, s, c);
	if (!tab)
		return (NULL);
	return (tab);
}
