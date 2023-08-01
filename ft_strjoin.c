/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egervais <egervais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 15:23:28 by egervais          #+#    #+#             */
/*   Updated: 2023/07/17 22:00:03 by egervais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
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
	i = 0;
	while (i < len)
	{
		substr[i] = s[start + i];
		i++;
	}
	substr[i] = '\0';
	return (substr);
}

static char	*ft_fill(const char *s1, const char *s2, char *f, int i)
{
	int	z;

	z = 0;
	while (s1[z])
	{
		f[z] = s1[z];
		z++;
	}
	z = 0;
	while (s2[z])
	{
		f[i + z] = s2[z];
		z++;
	}
	f[i + z] = 0;
	return (f);
}

char	*ft_strjoin(char *s1, char *s2)
{
	int		i;
	int		c;
	char	*f;

	if (!s1 || !s2)
		return (NULL);
	i = ft_strlen(s1);
	c = ft_strlen(s2);
	f = malloc(sizeof(char) * (c + i + 1));
	if (!f)
		return (NULL);
	f = ft_fill(s1, s2, f, i);
	return (f);
}

char	*ft_strstr(char *str, char *to_find)
{
	int	i;
	int	stop;

	if (*to_find == '\0')
		return (str);
	while (*str != '\0')
	{
		if (*str == *to_find)
		{
			i = 0;
			stop = 0;
			while (to_find[i] != '\0')
			{
				if (str[i] != to_find[i])
					stop = 1;
				i++;
			}
			if (stop == 0)
				return (str);
		}
		str++;
	}
	return (0);
}
