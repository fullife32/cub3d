/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eassouli <eassouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 16:15:23 by eassouli          #+#    #+#             */
/*   Updated: 2021/01/05 16:28:22 by eassouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_strclen(const char *s, char c)
{
	int				i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == c)
			return (i);
		i++;
	}
	if (s[i] == c)
		return (i);
	return (-1);
}

int	ft_slen(char *s)
{
	if (s)
		return (ft_strclen(s, '\0'));
	return (0);
}

char	*ft_strcjoin(char *s1, char *s2)
{
	int				i;
	int				j;
	char			*str;

	i = ft_slen(s1);
	j = ft_slen(s2);
	str = malloc(sizeof(char) * (i + j + 1));
	if (str == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (s1 && s1[i] != '\0')
	{
		str[i] = s1[i];
		i++;
	}
	while (s2 && s2[j] != '\n' && s2[j] != '\0')
	{
		str[i + j] = s2[j];
		j++;
	}
	str[i + j] = '\0';
	if (s1)
		free(s1);
	return (str);
}

void	ft_memcmove(void *dst, const void *src, size_t len)
{
	unsigned char	*dest;
	unsigned char	*source;

	dest = dst;
	source = (unsigned char *)src;
	while (--len != 0)
		*dest++ = *source++;
}
