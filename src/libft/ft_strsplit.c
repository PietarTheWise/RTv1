/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnoutere <pnoutere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 13:11:47 by pnoutere          #+#    #+#             */
/*   Updated: 2021/12/02 17:20:45 by pnoutere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_word_count(char const *s, char c)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (s[i])
	{
		if (i == 0 && s[0] != c)
			count++;
		if (s[i] == c && s[i + 1] != c && s[i + 1] != '\0')
			count++;
		i++;
	}
	return (count);
}

static char	**ft_free_arr(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		array[i] = NULL;
		i++;
	}
	free(array);
	array = NULL;
	return (array);
}

static int	find_start(char const *s, char c, int i)
{
	while (s[i] == c)
		i++;
	return (i);
}

char	**ft_strsplit(char const *s, char c)
{
	char	**str;
	int		start;
	int		i;
	int		j;

	j = 0;
	if (!s)
		return (NULL);
	str = (char **)malloc(sizeof(char *) * (ft_word_count(s, c) + 1));
	if (!str)
		return (NULL);
	i = 0;
	while (ft_word_count(s, c) > j)
	{
		i = find_start(s, c, i);
		start = i;
		while (s[i] && s[i] != c)
			i++;
		str[j] = ft_strsub(s, start, i - start);
		if (!str[j])
			return (ft_free_arr(str));
		j++;
	}
	str[j] = NULL;
	return (str);
}
