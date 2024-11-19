/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_parser_buffer_fill.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 14:54:09 by kiroussa          #+#    #+#             */
/*   Updated: 2024/11/19 02:28:10 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <fcntl.h>
#include <ft/io.h>
#include <ft/mem.h>
#include <ft/string.h>
#define __RT_PARSER_INTERNAL__
#include <rt/parser.h>
#include <string.h>
#include <unistd.h>

#define FILE_EXTENSION ".rt"

static RESULT	rt_parser_buffer_count_lines(char *buffer, size_t offset,
					size_t *nl, RESULT res)
{
	size_t	nlines;
	size_t	i;

	buffer[offset] = '\0';
	nlines = 0;
	i = 0;
	while (buffer[i])
	{
		if (buffer[i] == '\n')
			nlines++;
		i++;
	}
	*nl = nlines;
	return (res);
}

static RESULT	rt_parser_buffer_fill_fd(const char *filepath, char *buffer,
					size_t len, size_t *nlines)
{
	RESULT	res;
	ssize_t	nread;
	size_t	offset;
	int		fd;

	if (buffer == NULL)
		return (ERRS(PARSE_ERR_ALLOC, "cannot allocate file buffer"));
	fd = open(filepath, O_RDONLY);
	res = OK();
	offset = 0;
	if (fd == -1)
		return (ERRS(PARSE_ERR_FILE_READ, "'%s' cannot be opened: %s",
				filepath, strerror(errno)));
	while (RES_OK(res) && offset < len)
	{
		nread = read(fd, buffer + offset, len - offset);
		if (nread == -1)
			res = ERRD(PARSE_ERR_FILE_READ, "error while reading file: %m");
		else
			offset += nread;
	}
	close(fd);
	if (!RES_OK(res))
		return (res);
	return (rt_parser_buffer_count_lines(buffer, offset, nlines, res));
}

__always_inline __attribute__((nonnull))
static RESULT	rt_parser_check_filename(const char *filepath)
{
	const char	*ext;

	ext = ft_strrchr(filepath, '.');
	if (ext == NULL)
		return (ERRS(PARSE_ERR_FILE_READ, "'%s' has no extension", filepath));
	if (ft_strcmp(ext, FILE_EXTENSION) != 0)
		return (ERRS(PARSE_ERR_FILE_READ, "'%s' is not a %s file", filepath,
				FILE_EXTENSION));
	return (OK());
}

__attribute__((nonnull(1, 3)))
static RESULT	rt_parser_buffer_alloc_fd(const char *filepath, int fd,
					char **buffer, size_t *nlines)
{
	RESULT	res;
	size_t	len;
	ssize_t	nread;
	char	dummy[8192];

	res = OK();
	len = 0;
	nread = sizeof(dummy);
	while (RES_OK(res) && nread == sizeof(dummy))
	{
		nread = read(fd, dummy, sizeof(dummy));
		if (nread == -1)
			res = ERRD(PARSE_ERR_FILE_READ, "error while reading file: %m");
		len += (nread != -1) * nread;
	}
	if (!RES_OK(res))
		return (res);
	if (len == 0)
		close(fd);
	if (len == 0)
		return (ERRS(PARSE_ERR_FILE_READ, "'%s' is empty", filepath));
	*buffer = ft_calloc(1, len + 1);
	close(fd);
	return (rt_parser_buffer_fill_fd(filepath, *buffer, len, nlines));
}

RESULT	rt_parser_buffer_fill(t_rt_parser *parser, const char *filepath)
{
	RESULT	res;
	int		fd;

	if (filepath == NULL || parser == NULL)
		return (ERR(PARSE_ERR_NULL));
	res = rt_parser_check_filename(filepath);
	if (!RES_OK(res))
		return (res);
	fd = open(filepath, O_RDWR);
	if (fd == -1)
	{
		if (errno == EISDIR)
			return (ERRS(PARSE_ERR_FILE_READ, "'%s' is a directory", filepath));
		fd = open(filepath, O_RDONLY);
	}
	if (fd == -1)
		return (ERRS(PARSE_ERR_FILE_READ, "'%s' cannot be opened: %s",
				filepath, strerror(errno)));
	return (rt_parser_buffer_alloc_fd(filepath, fd, &parser->read_buffer,
			&parser->nlines));
}
