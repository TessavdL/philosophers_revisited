/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   time.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: tessa <tessa@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/30 20:45:52 by tessa         #+#    #+#                 */
/*   Updated: 2022/03/01 13:24:17 by tevan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

long int	get_time_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

static long int	get_time_us(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (((tv.tv_sec * 1000) * 1000) + tv.tv_usec);
}

static void	let_time_pass_expect_no_death(long int us)
{
	long int	start;

	start = get_time_us();
	while (get_time_us() - start < us)
	{
		usleep(100);
	}
}

static void	let_time_pass_expect_death(t_philosopher *phil, long int us)
{
	long int	start;

	start = get_time_us();
	while (get_time_us() - start < us)
	{
		usleep(100);
		if (get_set_status(GET, phil->mutexes.dead, phil->dead, -1)
			== TRUE)
		{
			return ;
		}
	}
}

int	let_time_pass(t_philosopher *phil, int time)
{
	if (time > phil->data.time_until_death)
	{
		let_time_pass_expect_death(phil, time * 1000);
		return (1);
	}
	else
	{
		let_time_pass_expect_no_death(time * 1000);
		return (0);
	}
}
