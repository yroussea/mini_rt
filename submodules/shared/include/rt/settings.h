/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   settings.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 18:10:03 by kiroussa          #+#    #+#             */
/*   Updated: 2024/10/16 18:14:25 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SETTINGS_H
# define SETTINGS_H
# undef SETTINGS_H
# ifndef __RT_SETTINGS_H__
#  define __RT_SETTINGS_H__

#  include <rt/color.h>
#  include <stdbool.h>

enum e_rt_setting_type
{
	SETTING_TYPE_BOOL = 0,
	SETTING_TYPE_INT,
	SETTING_TYPE_DOUBLE,
	SETTING_TYPE_STRING,
	SETTING_TYPE_COLOR,
	SETTING_TYPE_KEYBIND,
};

typedef struct s_rt_setting
{
	const char				*name;
	const char				*description;
	enum e_rt_setting_type	type;
	union
	{
		bool				v_bool;
		int					v_int;
		double				v_double;
		const char			*v_double;
		t_color				v_color;
		int					v_keybind;
	}	u_value;
}	t_rt_setting;

# endif // __RT_SETTINGS_H__
#endif // SETTINGS_H
