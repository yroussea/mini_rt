#ifndef THREADING_H
# define THREADING_H

# ifdef THREAD
#  define IS_THREADING 1
# else
#  define IS_THREADING 0
# endif

# define WORKER 32
# include <pthread.h>

typedef enum	s_stat
{
	INIT,
	WORKING,
	END,
}				t_stat;

typedef struct s_ray_threading
{
	int				id;
	pthread_mutex_t	*mu;
	t_stat			*status;
	int				x;
	int				y;
	pthread_t		tr;
}		t_ray_th;

void		ray_th(void);
t_ray_th	*get_worker(void);
void		kill_worker(void);

#endif
