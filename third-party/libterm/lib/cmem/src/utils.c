/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgramati <rgramati@student.42angouleme.fr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 19:32:49 by rgramati          #+#    #+#             */
/*   Updated: 2024/11/18 00:13:58 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cmem.h>
#include <stdlib.h>

uint32_t	cm_min(uint32_t a, uint32_t b)
{
	if (a < b)
		return (a);
	return (b);
}

uint32_t	cm_twos_power_raise(uint32_t x)
{
	x += !x;
	x--;
	x |= x >> 1;
	x |= x >> 2;
	x |= x >> 4;
	x |= x >> 8;
	x |= x >> 16;
	x++;
	return (x);
}

uint32_t	cm_strlen(const char *str)
{
	const char	*tmp;

	tmp = str;
	while (*tmp)
		tmp++;
	return (tmp - str);
}

int32_t	cm_strcmp(const char *s1, const char *s2)
{
	while (*s1 == *s2 && *s1)
	{
		s1++;
		s2++;
	}
	return (*s1 - *s2);
}

char	*cm_strdup(const char *str)
{
	char		*cpy;
	uint32_t	len;

	len = cm_strlen(str);
	cpy = malloc(len + 1);
	if (cpy)
	{
		cm_memcpy(cpy, (void *)str, len);
		cpy[len] = 0;
	}
	return (cpy);
}
