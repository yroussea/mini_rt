/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlopen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 02:56:50 by kiroussa          #+#    #+#             */
/*   Updated: 2024/10/26 02:30:45 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/mem.h>
#define __RT_DEVRELOAD_DLFCN_INTERNAL__
#include <rt/devreload/dlfcn.h>

static int	find_size(int fd, size_t *size)
{
	char	buffer[8096];
	ssize_t	read_size;

	ft_memset(buffer, 0, sizeof(buffer));
	while (1)
	{
		read_size = read(fd, buffer, sizeof(buffer));
		if (read_size == -1)
			return (-1);
		*size += read_size;
		if (read_size != sizeof(buffer))
			break ;
	}
	return (0);
}

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

static void	hexdump(void *start, size_t size)
{
	size_t	i;
	unsigned char	*ptr = (unsigned char *) start;

	for (i = 0; i < size; i++)
	{
		printf("%02x ", ptr[i]);
		if (i % 16 == 15)
			printf("\n");
		else if (i % 8 == 7)
			printf(" ");
	}
}

static void	dump_got(void *start)
{
	void	*got_start = start + 0x4000;
	size_t	got_size = 0x26;

	hexdump(got_start, got_size);
}

void	*ft_dlopen(const char *path, __attribute__((unused)) int ignored)
{
	const int	fd = open(path, O_RDONLY);
	t_dl_info	*dl_info;
	size_t		file_size;

	if (fd == -1)
		return (NULL);
	dl_info = ft_calloc(1, sizeof(t_dl_info));
	if (!dl_info)
	{
		close(fd);
		return (NULL);
	}
	file_size = 0;
	if (find_size(fd, &file_size) == -1)
	{
		close(fd);
		free(dl_info);
		return (NULL);
	}
	RT_DEBUG("file_size: %d\n", (int) file_size);
	dl_info->start = ft_mmap(NULL, file_size, PROT_READ | PROT_EXEC,
			MAP_PRIVATE, fd, 0);
	RT_DEBUG("dl_info->start: %p\n", dl_info->start);
	dl_info->size = file_size;
	dump_got(dl_info->start);
	return (dl_info);
}
