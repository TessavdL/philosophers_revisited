/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   monitoring.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: tevan-de <tevan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/04 12:14:03 by tevan-de      #+#    #+#                 */
/*   Updated: 2022/02/04 12:37:13 by tevan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

static t_bool	check_if_phil_is_dead(t_philosopher *phil)
{
	long int	time_of_last_meal;

	time_of_last_meal = get_time_of_last_meal(&phil->mutexes.time_of_last_meal,
		phil->time_of_last_meal);
	if (time_of_last_meal - get_time() >= phil->data.time_until_death)
	{
		return (TRUE);
	}
	return (FALSE);
}

void	*monitoring(void *ptr)
{
	t_philosopher	*phil;

	phil = (t_philosopher *)ptr;
	while (1)
	{
		if (check_if_phil_is_dead(phil) == TRUE)
		{
			set_status(&phil->mutexes.dead, phil->dead, TRUE);
			print_message(&phil->mutexes.print, phil->id, get_time(),
				"has died\n");
			break ;
		}
		if (phil->data.number_of_meals != UNINITIALIZED
			&& get_status(&phil->mutexes.full, phil->full) == TRUE)
		{
			break ;
		}
		usleep(500);
	}
	return (NULL);
}
