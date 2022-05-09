/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cthien-h <cthien-h@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/13 20:39:37 by cthien-h          #+#    #+#             */
/*   Updated: 2021/05/16 16:04:53 by cthien-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	count_words(const char *str, char c)
{
	size_t	words;
	int		in_word;

	words = 0;
	in_word = 0;
	while (*str)
	{
		if (*str != c && !in_word)
		{
			words++;
			in_word = 1;
		}
		else if (*str == c)
		{
			in_word = 0;
		}
		str++;
	}
	return (words);
}

static int	split_words(char const *s, char c, char **arr)
{
	size_t	word_len;

	while (*s)
	{
		word_len = 0;
		while (s[word_len] && s[word_len] != c)
			word_len++;
		if (word_len)
		{
			*arr = (char *)ft_calloc(word_len + 1, sizeof(char));
			if (!*arr)
				return (0);
			ft_strlcpy(*arr, s, word_len + 1);
			arr++;
			s = &s[word_len];
		}
		else
		{
			s++;
		}
	}
	return (42);
}

static char	**free_all(char **arr)
{
	size_t	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	char	**arr;

	arr = (char **)ft_calloc(count_words(s, c) + 1, sizeof(char *));
	if (arr && !split_words(s, c, arr))
		return (free_all(arr));
	return (arr);
}
