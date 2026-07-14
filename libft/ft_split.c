/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acasper <acasper@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 23:45:27 by acasper           #+#    #+#             */
/*   Updated: 2025/06/03 18:24:39 by acasper          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	counter(const char *s, char c)
{
	int	count;
	int	found;

	count = 0;
	found = 0;
	while (*s)
	{
		if (*s != c && found == 0)
		{
			found = 1;
			count++;
		}
		else if (*s == c)
			found = 0;
		s++;
	}
	return (count);
}

char	*malloc_word(char const *start, int len)
{
	char	*word;
	int		i;

	word = (char *)malloc(sizeof(char) * (len + 1));
	if (!word)
		return (NULL);
	i = 0;
	while (i < len)
	{
		word[i] = start[i];
		i++;
	}
	word[i] = '\0';
	return (word);
}

void	free_word(char **str, int i)
{
	while (i--)
	{
		free(str[i]);
	}
	free(str);
}

int	fill_words(char **str, const char *s, char c)
{
	int	word_len;
	int	i;

	i = 0;
	while (*s)
	{
		if (*s == c)
		{
			s++;
			continue ;
		}
		word_len = 0;
		while (s[word_len] && s[word_len] != c)
			word_len++;
		str[i] = malloc_word(s, word_len);
		if (!str[i])
		{
			free_word(str, i);
			return (0);
		}
		i++;
		s += word_len;
	}
	str[i] = NULL;
	return (1);
}

char	**ft_split(char const *s, char c)
{
	char	**str;
	int		word_count;

	if (!s)
		return (NULL);
	word_count = counter(s, c);
	str = (char **)malloc(sizeof(char *) * (word_count + 1));
	if (!str)
		return (NULL);
	if (!fill_words(str, s, c))
		return (NULL);
	return (str);
}
/*
int	main(void)
{
	char	**string;
	int		i;

	string = ft_split("meow miau meow", ' ');
	i = 0;
	while (string[i])
	{
		printf("meow miau meow, ' ': %s\n", string[i]);
		i++;
	}
	//	i = 0;
	//	while (string[i])
	//		free(string[i]);
	//	free(string);
	return (0);
}
*/
