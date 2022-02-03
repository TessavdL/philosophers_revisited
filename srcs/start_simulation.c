/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   start_simulation.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: tessa <tessa@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/27 15:41:00 by tessa         #+#    #+#                 */
/*   Updated: 2022/02/03 22:25:36 by tessa         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

// static t_bool	check_if_philosopher_is_dead(t_philosopher *phil)
// {
// 	pthread_mutex_lock(&phil->mutexes[TIME]);
// 	if (phil->data.time_until_death <= )
// }

// static void	monitoring(void *ptr)
// {
// 	t_philosopher	*phil;

// 	phil = (t_philosopher*)ptr;
// 	while (1)
// 	{
// 		if (check_if_philosopher_is_dead(phil) == TRUE)
// 		{
// 			break ;
// 		}
// 		if (phil->data.number_of_meals != UNINITIALIZED &&
// 			phil->data.number_of_meals != 0)
// 		{
// 			break ;
// 		}
// 	}
// }

// static int	start_monitoring(t_philosopher *philosophers)
// {
// 	int	i;

// 	i = 0;
// 	while (i < philosophers[0].data.number_of_philosophers)
// 	{
// 		if (pthread_create(&philosophers[i].monitoring, NULL, &monitoring,
// 			&philosophers[i]))
// 		{
// 			return (1);
// 		}
// 		usleep(500);
// 		i++;
// 	}
// 	return (0);	
// }

int	start_simulation(t_philosopher *philosophers, int number_of_philosophers)
{
	int	i;

	i = 0;
	while (i < number_of_philosophers)
	{
		if (pthread_create(&philosophers[i].thread.simulation, NULL, &eat_sleep_think,
			&philosophers[i]))
		{
			return (1);
		}
		i++;
	}
	i = 0;
	while (i < number_of_philosophers)
	{
		if (pthread_join(philosophers[i].thread.simulation, NULL))
		{
			return (1);
		}
		i++;
	}
	// start_monitoring(philosophers);
	printf("%d %d %d %d %d\n", philosophers[0].data.number_of_philosophers,
	philosophers[0].data.time_until_death, philosophers[0].data.time_to_eat,
	philosophers[0].data.time_to_sleep, philosophers[0].data.number_of_meals);
	return (0);
}
