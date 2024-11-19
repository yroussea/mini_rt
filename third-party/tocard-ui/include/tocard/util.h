/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 23:38:05 by kiroussa          #+#    #+#             */
/*   Updated: 2024/10/14 19:26:35 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTIL_H
# define UTIL_H
# undef UTIL_H
# ifndef __TOCARD_UTIL_H__
#  define __TOCARD_UTIL_H__

#  include <stddef.h>

// /* Standard utils */ //

size_t		toc_strlen(const char *s);
int			toc_strcmp(const char *s1, const char *s2);
int			toc_strcmp_ignorecase(const char *s1, const char *s2);
int			toc_min(int a, int b);

// /* Vectors */ //

typedef struct s_toc_vec2i
{
	int	x;
	int	y;
}	t_toc_vec2i;

t_toc_vec2i	toc_vec2i(int x, int y);
t_toc_vec2i	toc_vec2i_add(t_toc_vec2i a, t_toc_vec2i b);

// /* Colors */ //

typedef union u_toc_color
{
	unsigned int	value;
	struct
	{
		unsigned char	b;
		unsigned char	g;
		unsigned char	r;
		unsigned char	a;
	};
}	t_toc_color;

t_toc_color	toc_color_rgba(unsigned char r, unsigned char g, unsigned char b,
				unsigned char a);
t_toc_color	toc_color_rgb(unsigned char r, unsigned char g, unsigned char b);
t_toc_color	toc_color(unsigned int value);

// /* Linked List */ //

typedef struct s_toc_list
{
	void				*data;
	struct s_toc_list	*next;
}	t_toc_list;

typedef void (t_destroy_fn)(void *data);

t_toc_list	*toc_list_create(void *data);
void		toc_list_clear(t_toc_list **list, t_destroy_fn *destroy);

void		toc_list_push(t_toc_list **list, t_toc_list *node);
void		toc_list_remove(t_toc_list **list, t_toc_list *node,
				t_destroy_fn *destroy);

# endif // __TOCARD_UTIL_H__
#endif // UTIL_H
