/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termengine.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgramati <rgramati@student.42angouleme.fr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 14:15:54 by rgramati          #+#    #+#             */
/*   Updated: 2024/11/18 01:01:36 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TERMENGINE_H
# define TERMENGINE_H

# include <unistd.h>
# include <stdint.h>
# include <termios.h>
# include <sys/ioctl.h>

# define CM_INCLUDE_ALL
# include <cmem.h>

# define TE_COLOR_TABLE "000\000001\000002\000003\000004\000005\000006\
000007\000008\
\000009\000010\000011\000012\000013\000014\000015\000\
016\000017\000018\000019\000020\000021\000022\000023\000\
024\000025\000026\000027\000028\000029\000030\000031\000\
032\000033\000034\000035\000036\000037\000038\000039\000\
040\000041\000042\000043\000044\000045\000046\000047\000\
048\000049\000050\000051\000052\000053\000054\000055\000\
056\000057\000058\000059\000060\000061\000062\000063\000\
064\000065\000066\000067\000068\000069\000070\000071\000\
072\000073\000074\000075\000076\000077\000078\000079\000\
080\000081\000082\000083\000084\000085\000086\000087\000\
088\000089\000090\000091\000092\000093\000094\000095\000\
096\000097\000098\000099\000100\000101\000102\000103\000\
104\000105\000106\000107\000108\000109\000110\000111\000\
112\000113\000114\000115\000116\000117\000118\000119\000\
120\000121\000122\000123\000124\000125\000126\000127\000\
128\000129\000130\000131\000132\000133\000134\000135\000\
136\000137\000138\000139\000140\000141\000142\000143\000\
144\000145\000146\000147\000148\000149\000150\000151\000\
152\000153\000154\000155\000156\000157\000158\000159\000\
160\000161\000162\000163\000164\000165\000166\000167\000\
168\000169\000170\000171\000172\000173\000174\000175\000\
176\000177\000178\000179\000180\000181\000182\000183\000\
184\000185\000186\000187\000188\000189\000190\000191\000\
192\000193\000194\000195\000196\000197\000198\000199\000\
200\000201\000202\000203\000204\000205\000206\000207\000\
208\000209\000210\000211\000212\000213\000214\000215\000\
216\000217\000218\000219\000220\000221\000222\000223\000\
224\000225\000226\000227\000228\000229\000230\000231\000\
232\000233\000234\000235\000236\000237\000238\000239\000\
240\000241\000242\000243\000244\000245\000246\000247\000\
248\000249\000250\000251\000252\000253\000254\000255\000"

# define TE_W				384
# define TE_H				108

# define TE_BLEN			41
# define TE_BLOCK			"▄"

# define TE_BACKGROUND		0
# define TE_FOREGROUND		1

# define TE_MODE_RENDER		1
# define TE_MODE_BACKUP		0

# define TE_EOF				'\x04'
# define TE_ESQ				'\x1b'

# define TE_ANSI_RGB_BG		"\033[48;2"
# define TE_ANSI_RGB_FG		"\033[38;2"
# define TE_ANSI_RESET		"\033[0m"
# define TE_ANSI_CLEAR		"\033c"
# define TE_ANSI_HOME		"\033[H"
# define TE_ANSI_CURSOR_ON	"\033[?25h"
# define TE_ANSI_CURSOR_OFF	"\033[?25l"

typedef enum e_rgb_colors
{
	TE_RGB_BLACK		= 0x00000000,
	TE_RGB_RED			= 0xFFFF0000,
	TE_RGB_GREEN		= 0xFF00FF00,
	TE_RGB_BLUE			= 0xFF0000FF,
	TE_RGB_YELLOW		= TE_RGB_RED | TE_RGB_GREEN,
	TE_RGB_CYAN			= TE_RGB_GREEN | TE_RGB_BLUE,
	TE_RGB_MAGENTA		= TE_RGB_BLUE | TE_RGB_RED,
	TE_RGB_WHITE		= ~TE_RGB_BLACK,
	TE_RGB_TRANSPARENT	= TE_RGB_MAGENTA
}	t_rgb_colors;

typedef uint8_t				*t_screen;

typedef struct s_terminal	t_terminal;

typedef struct s_hook_tab	t_hook_tab;

typedef struct s_te_img		t_te_img;

typedef struct s_te_anim	t_te_anim;

typedef struct s_llist
{
	uint32_t		index;
	struct s_llist	*next;
}	t_llist;

typedef struct s_vec2
{
	int32_t	x;
	int32_t	y;
}	t_vec2;

typedef struct s_fvec2
{
	float	x;
	float	y;
}	t_fvec2;

/* TERMINAL ***************************************************************** */

# define TE_HOOK	te_terminal_hook

enum e_hook_types
{
	TE_KEYDOWN,
	TE_LOOP,
	TE_ESCAPE = 128,
};

typedef void				*(*t_hook_func)(void *);

struct s_hook_tab
{
	t_hook_func	hooks[256];
	void		*params[256];
	uint8_t		states[256];
};

struct s_terminal
{
	uint32_t		col;
	uint32_t		row;
	uint32_t		fps;
	uint32_t		active;
	t_cm_chunk		*images;
	t_screen		screen;
	t_screen		back;
	t_hook_tab		hook_table;
};

t_terminal
*te_init(void);

void
te_destroy(t_terminal *t);

void
te_loop(t_terminal *t);

void
te_loop_end(t_terminal *t);

void
te_terminal_fps_max(t_terminal *t, uint32_t fps);

void
te_sleep(uint32_t usecs);

void
te_terminal_hook(t_terminal *t, uint32_t type, t_hook_func func, void *param);

t_screen
te_screen_init(t_terminal *t);

void
te_screen_destroy(t_screen screen);

void
te_screen_set_pixel(t_terminal *t, t_vec2 pos, uint32_t color);

void
te_screen_get_pixel(t_terminal *t, t_vec2 pos, uint32_t *color);

void
te_screen_put_img(t_terminal *t, t_te_img *img, t_vec2 pos);

void
te_screen_draw_line(t_terminal *t, t_vec2 start, t_vec2 end, uint32_t color);

void
te_screen_draw_square(t_terminal *t, t_vec2 start, t_vec2 size, uint32_t color);

void
te_terminal_screen_shift(t_terminal *t);

void
te_ansi(const char *seq);

/* IMAGES ****************************************************************** */

struct s_te_img
{
	uint32_t	col;
	uint32_t	row;
	uint32_t	x;
	uint32_t	y;
	uint32_t	*data;
};

void
te_img_init(t_te_img *img, uint32_t row, uint32_t col, uint32_t *data);

void
te_img_destroy(t_te_img *img);

void
te_img_set_pixel(t_te_img *img, t_vec2 pos, uint32_t color);

void
te_img_get_pixel(t_te_img *img, t_vec2 pos, uint32_t *color);

/* SCREEN ****************************************************************** */

void
te_str_append(const char *src, char *dst, char **remain);

void
te_str_append_color(uint32_t mode, uint32_t color, char *cursor, char **remain);

#endif
