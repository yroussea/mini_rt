/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   toc_strcmp_ignorecase.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 18:01:31 by kiroussa          #+#    #+#             */
/*   Updated: 2024/05/24 18:01:32 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	toc_tolower(int c)
{
	if (c >= 'A' && c <= 'Z')
		return (c + 'a' - 'A');
	return (c);
}

int	toc_strcmp_ignorecase(const char *s1, const char *s2)
{
	while (*s1 && *s2)
	{
		if (toc_tolower(*s1) != toc_tolower(*s2))
			return (toc_tolower(*s1) - toc_tolower(*s2));
		s1++;
		s2++;
	}
	return (toc_tolower(*s1) - toc_tolower(*s2));
}
