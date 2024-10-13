#include <math.h>
#include <stdbool.h>
#include <stdio.h>

int	bigger_divisor(int n, int actual)
{
	int	x;

	x = actual + 1;
	while (x < n)
	{
		if (!(n % x))
			return (x);
		x++;
	}
	return (n);
}

int	smaller_divisor(int n, int actual)
{
	int	x;

	x = actual - 1;
	while (x > 1)
	{
		if (!(n % x))
			return (x);
		x--;
	}
	return (1);
}

int	next_size(int width, int height, int actual, bool bigger)
{
	int	x;

	x = actual;
	if (bigger)
	{
		while (x < width)
		{
			x = bigger_divisor(width, x);
			if (!(height % x))
				return (x);
		}
		return (actual);
	}
	while (1)
	{
		x = smaller_divisor(width, x);
		if (!(height % x))
			return (x);
	}
	return (1);
}
