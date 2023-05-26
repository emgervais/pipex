/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egervais <egervais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 17:51:58 by egervais          #+#    #+#             */
/*   Updated: 2023/05/22 17:33:21 by egervais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_strlen(const char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_substrr(char const *s, unsigned int start, size_t len)
{
	unsigned int	i;
	unsigned int	s_len;
	char			*substr;

	if (!s)
		return (NULL);
	s_len = ft_strlen(s);
	if (s_len < start)
		len = 0;
	if (len > s_len - start)
		len = s_len - start;
	substr = malloc(sizeof(*s) * (len + 2));
	if (!substr)
		return (NULL);
	i = -1;
	while (++i < len)
		substr[i] = s[start + i];
	substr[i] = '/';
	substr[i + 1] = '\0';
	return (substr);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	unsigned int	i;
	unsigned int	s_len;
	char			*substr;

	if (!s)
		return (NULL);
	s_len = ft_strlen(s);
	if (s_len < start)
		len = 0;
	if (len > s_len - start)
		len = s_len - start;
	substr = malloc(sizeof(*s) * (len + 1));
	if (!substr)
		return (NULL);
	i = -1;
	while (++i < len)
		substr[i] = s[start + i];
	substr[i] = '\0';
	return (substr);
}

int	ft_count_word(char const *s, char c)
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

static char	**filltab(char **tab, char const *s, char c, int mode)
{
	int		i;
	int		word;
	int		size;
	int		j;

	i = 0;
	j = -1;
	word = ft_count_word(s, c);
	while (++j < word)
	{
		while (s[i] == c)
			i++;
		size = ft_size_word(s, c, i);
		if(mode)
			tab[j] = ft_substr(s, i, size);
		else
			tab[j] = ft_substrr(s, i, size);
		if (!tab[j])
		{
			ft_free(tab, j);
			return (NULL);
		}
		i += size;
	}
	return (tab);
}

char	**ft_split(char const *s, char c, int mode)
{
	int		word;
	char	**tab;

	if (!s)
		return (NULL);
	word = ft_count_word(s, c);
	tab = (char **)malloc((word + 1) * sizeof(char *));
	if (!tab)
		return (NULL);
	tab = filltab(tab, s, c, mode);
	tab[word] = 0;
	if (!tab)
		return (NULL);
	return (tab);
}
