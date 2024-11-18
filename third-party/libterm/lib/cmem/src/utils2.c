/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 00:12:26 by kiroussa          #+#    #+#             */
/*   Updated: 2024/11/18 00:14:04 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cmem.h>
#include <stdint.h>

void	cm_memset(void *ptr, unsigned char c, uint32_t n)
{
	while (n && (uintptr_t)ptr & (sizeof(uint64_t) - 1))
	{
		*(uint8_t *)ptr = c;
		ptr++;
		n--;
	}
	while (n >= sizeof(uint64_t))
	{
		*(uint64_t *)ptr = c * (-1UL / 255);
		ptr += sizeof(uint64_t);
		n -= sizeof(uint64_t);
	}
	while (n)
	{
		*(uint8_t *)ptr = c;
		ptr++;
		n--;
	}
}

void	cm_memcpy(void *dst, void *src, uint32_t n)
{
	while (n && (uintptr_t)src & (sizeof(uint64_t) - 1))
	{
		*(uint8_t *)dst = *(uint8_t *)src;
		n--;
		src++;
		dst++;
	}
	while (n >= sizeof(uint64_t))
	{
		*(uint64_t *)dst = *(uint64_t *)src;
		n -= sizeof(uint64_t);
		src += sizeof(uint64_t);
		dst += sizeof(uint64_t);
	}
	while (n)
	{
		*(uint8_t *)dst = *(uint8_t *)src;
		n--;
		src++;
		dst++;
	}
}
