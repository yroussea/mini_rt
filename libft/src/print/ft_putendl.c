/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xtrm <oss@xtrm.me>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 18:22:12 by xtrm              #+#    #+#             */
/*   Updated: 2024/06/27 03:10:43 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/print.h>
#include <unistd.h>

int	ft_putendl(const char *str)
{
	return (ft_putendl_fd(str, STDOUT_FILENO));
}