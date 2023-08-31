/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ancolmen <ancolmen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 12:41:25 by ancolmen          #+#    #+#             */
/*   Updated: 2023/02/13 15:02:01 by ancolmen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	str_count(char const *str, char c)
{
	int	i;
	int	count;
	int	trigger;

	i = 0;
	count = 0;
	trigger = 1;
	while (str[i])
	{
		if (str[i] != c)
		{
			if (trigger == 1)
				count++;
			trigger = 0;
		}
		else
			trigger = 1;
		i++;
	}
	return (count);
}

static char	*get_str(char const *str, char c, int *i)
{
	char	*res;
	int		pos;
	int		len;

	len = 0;
	while (str[*i] && str[*i] != c)
	{
		(*i)++;
		len++;
	}
	res = (char *)ft_calloc((len + 1), sizeof(char));
	if (!res)
		return (NULL);
	pos = 0;
	while (pos < len)
	{
		res[pos] = str[*i - len + pos];
		pos++;
	}
	return (res);
}

static void	clean_memory(char **res, int x)
{
	int	i;

	i = 0;
	while (i < x)
	{	
		free(res[i]);
		i++;
	}
	free(res);
}

char	**ft_split(char const *s, char c)
{
	char	**res;
	int		i;
	int		j;

	res = (char **)ft_calloc((str_count(s, c) + 1), sizeof(char *));
	if (!res)
		return (NULL);
	i = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			res[j] = get_str(s, c, &i);
			if (res[j++] == 0)
			{
				clean_memory(res, j);
				return (NULL);
			}
		}
		else
			i++;
	}
	return (res);
}
