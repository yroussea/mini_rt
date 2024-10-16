/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlopen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 02:56:50 by kiroussa          #+#    #+#             */
/*   Updated: 2024/10/16 03:54:17 by kiroussa         ###   ########.fr       */
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

void	*ft_dlopen(const char *path, __attribute__((unused)) int ignored)
{
	const int	fd = open(path, O_RDONLY | O_CLOEXEC);
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
	dl_info->size = file_size;
	return (dl_info);
}
