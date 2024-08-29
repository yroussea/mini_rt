#include <ray.h>
#include <maths.h>
#include <rt.h>
#include <threading.h>

#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>

t_stat	get_status(t_ray_th *data, int set)
{
	t_stat	res;

	pthread_mutex_lock(data->mu);
	if (set)
		*data->status = set >> 1;
	res = *data->status;
	pthread_mutex_unlock(data->mu);
	return (res);
}

void	one_ray_thread(t_ray ray, int x, int y, t_ray_th *data)
{
	static t_objs		*objs = NULL;
	static t_light		*lights = NULL;
	static int			**colors = NULL;
	t_objs				*obj_hit;
	int					pixel_color;

	pthread_mutex_lock(data->mu);
	if (!colors)
	{
		get_colors(&colors);
		get_objs(&objs);
		get_lights(&lights);
	}
	pthread_mutex_unlock(data->mu);
	eye_rays(&ray, get_width((float)x), get_height((float)y));
	if (find_hit(&ray, objs, &obj_hit) != INT_MAX)
		get_shade(objs, lights, obj_hit, &ray, 0);
	pixel_color = vec_to_rgb(ray.color);
	for (int j = 0; j < PIXEL; j += 1)
	{
		for (int k = 0; k < PIXEL; k += 1)
			colors[y + j][x + k] = pixel_color;
	}
}

int	next_line_thread(int *y, t_ray_th *data)
{
	static int	j = 0;

	if (j == -1 || *data->status != WORKING)
	{
		*data->status = INIT;
		j = 0;
		return (0);
	}
	*y = j;
	j += PIXEL;
	if (j >= HEIGHT)
		j = -1;
	return (1);
}

int	next_pixel_line(int *x, int id)
{
	static	int	tab[WORKER] = {0};

	*x = tab[id];
	tab[id]++;
	if (tab[id] >= WIDTH)
	{
		tab[id] = 0;
		return (0);
	}
	return (1);
}

void	*routine(void *var)
{
	t_ray			ray;
	t_ray_th		*data;
	int				x = 0;
	t_stat			stat;
	int				y = 0;

	ray.center = (t_v4f){0, 0, -100, 0};
	data = var;
	while ((stat = get_status(data, 0)) != END)
	{
		if (stat == INIT)
			usleep(100);
		while (stat == WORKING)
		{
			pthread_mutex_lock(data->mu);
			if (next_line_thread(&y, data) == 0)
			{
				pthread_mutex_unlock(data->mu);
				break ;
			}
			pthread_mutex_unlock(data->mu);
			while (next_pixel_line(&x, data->id))
				one_ray_thread(ray, x, y, data);
		}
	}
	return (NULL);
}

suseconds_t	ms_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

t_ray_th	*get_worker(void)
{
	static t_ray_th			*worker = NULL;
	pthread_mutex_t			*mu;
	static t_stat			status;

	if (!worker && IS_THREADING)
	{
		status = INIT;
		mu = calloc(sizeof(pthread_mutex_t), 1);
		worker = calloc(sizeof(t_ray_th), WORKER); //calloc
		for (int k = 0; k < WORKER; k++)
		{
			worker[k].id = k;
			worker[k].mu = mu;
			worker[k].status = &status;
			pthread_create(&worker[k].tr, NULL, routine, worker + k);
		}

	}
	return (worker);
}

void	kill_worker(void)
{
	t_ray_th			*worker;

	worker = get_worker();
	if (!worker)
		return ;
	for (int k = 0; k < WORKER; k++)
	{
		get_status(worker + k, END << 1);
		pthread_join((worker)[k].tr, NULL);
	}
}

void	ray_th(void)
{
	static t_ray_th			*worker = NULL;

	if (!worker)
		worker = get_worker();

	suseconds_t begin = ms_time();
	get_status(worker, WORKING << 1);
	while (get_status(&worker[0], 0) == WORKING)
		usleep(1000);
	suseconds_t end = ms_time();
	suseconds_t time_spent = (double)(end - begin);
	printf("Execution time: %.02f seconds\n", (double)time_spent / 1000);

}
