/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   semaphore_initialization.c                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: tevan-de <tevan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/28 15:13:17 by tevan-de      #+#    #+#                 */
/*   Updated: 2022/02/28 15:22:15 by tevan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	initialize_semaphores(t_semaphores *semaphores,
	int number_of_philosophers)
{
	sem_unlink("dead");
	semaphores->dead= sem_open("dead", O_CREAT, 0666, 1);
	if (semaphores->dead== SEM_FAILED)
		exit(ERROR_FAILED_TO_INITIALIZE_SEMAPHORE);
	sem_unlink("forks");
	semaphores->forks = sem_open("forks", O_CREAT, 0666, number_of_philosophers);
	if (semaphores->forks == SEM_FAILED)
		exit(ERROR_FAILED_TO_INITIALIZE_SEMAPHORE);
	sem_unlink("print");
	semaphores->print = sem_open("print", O_CREAT, 0666, 1);
	if (semaphores->print == SEM_FAILED)
		exit(ERROR_FAILED_TO_INITIALIZE_SEMAPHORE);
}
