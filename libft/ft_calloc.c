/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eassouli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 20:20:13 by eassouli          #+#    #+#             */
/*   Updated: 2019/10/26 11:49:58 by eassouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	size_t			i;
	unsigned char	*ptr;

	i = count * size;
	if (!(ptr = (unsigned char *)malloc(i)))
		return (NULL);
	while (i-- != 0)
		ptr[i] = '\0';
	return ((void *)ptr);
}
