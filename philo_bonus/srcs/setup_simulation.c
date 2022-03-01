/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   setup_simulation.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: tessa <tessa@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/27 13:22:15 by tessa         #+#    #+#                 */
/*   Updated: 2022/02/28 17:25:25 by tevan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

static void close_semaphores(t_philosopher **philosophers,
	int number_of_philosophers)
{
	char	*str;
	int		i;
	int		j;

	i = 0;
	while (i < number_of_philosophers)
	{
		str = ft_itoa(i);
		if (!str)
			exit (ERROR_MALLOC_FAILED);
		sem_unlink(str);
		sem_close(((*philosophers)[i]).semaphores.time_of_last_meal);
		free(str);
		i++;	
	}
	j = 0;
	while (j < number_of_philosophers)
	{
		str = ft_itoa(i + j);
		if (!str)
			exit (ERROR_MALLOC_FAILED);
		sem_unlink(str);
		sem_close(((*philosophers)[j]).semaphores.time_of_last_meal);
		free(str);
		j++;	
	}
}

static void	initialize_individual_semaphores(t_philosopher **philosophers,
	int number_of_philosophers)
{
	char	*str;
	int		i;
	int		j;

	i = 0;
	while (i < number_of_philosophers)
	{
		str = ft_itoa(i);
		if (!str)
			exit(ERROR_MALLOC_FAILED);
		sem_unlink(str);
		((*philosophers)[i]).semaphores.time_of_last_meal = sem_open(str,
			O_CREAT, 666, 1);
		if (((*philosophers)[i]).semaphores.time_of_last_meal == SEM_FAILED)
			exit(ERROR_FAILED_TO_INITIALIZE_SEMAPHORE);
		free(str);
		i++;
	}
	j = 0;
	while (j < number_of_philosophers)
	{
		str = ft_itoa(i + j);
		if (!str)
			exit(ERROR_MALLOC_FAILED);
		sem_unlink(str);
		((*philosophers)[j]).semaphores.time_of_last_meal = sem_open(str,
			O_CREAT, 666, 1);
		if (((*philosophers)[j]).semaphores.time_of_last_meal == SEM_FAILED)
			exit(ERROR_FAILED_TO_INITIALIZE_SEMAPHORE);
		j++;
		free(str);
	}
}

static void	initialize_philosophers(t_bool *dead, t_philosopher **philosophers,
	t_semaphores semaphores, t_input data)
{
	int	i;

	*philosophers = ft_calloc(sizeof(t_philosopher),
		data.number_of_philosophers);
	if (!(*philosophers))
	{
		exit(ERROR_MALLOC_FAILED);
	}
	i = 0;
	while (i < data.number_of_philosophers)
	{
		initialize_individual_semaphores(philosophers,
			data.number_of_philosophers);
		((*philosophers)[i]).semaphores.dead = semaphores.dead;
		((*philosophers)[i]).semaphores.forks = semaphores.forks;
		((*philosophers)[i]).semaphores.print = semaphores.print;
		((*philosophers)[i]).data = data;
		((*philosophers)[i]).dead = dead;
		((*philosophers)[i]).full = FALSE;
		((*philosophers)[i]).id = i + 1;
		i++;
	}
}

int	setup_simulation(t_input data, const int number_of_philosophers)
{
	t_bool			*dead;
	t_philosopher	*philosophers;
	t_semaphores	semaphores;

	dead = ft_calloc(sizeof(t_bool), 1);
	if (!dead)
	{
		exit(ERROR_MALLOC_FAILED);
	}
	initialize_semaphores(&semaphores, data.number_of_philosophers);
	initialize_philosophers(dead, &philosophers, semaphores, data);
	start_simulation(philosophers, number_of_philosophers);
	sem_unlink("dead");
	sem_unlink("forks");
	sem_unlink("print");
	sem_close(semaphores.dead);
	sem_close(semaphores.forks);
	sem_close(semaphores.print);
	close_semaphores(&philosophers, number_of_philosophers);
	free(dead);
	free(philosophers);
	return (0);
}
