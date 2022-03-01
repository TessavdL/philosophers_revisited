/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philosophers.h                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: tessa <tessa@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/22 13:02:29 by tessa         #+#    #+#                 */
/*   Updated: 2022/02/28 17:23:17 by tevan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# define UNINITIALIZED 0
# define CHILD 0
# define DEAD 0

# include <fcntl.h>
# include <pthread.h>
# include <unistd.h>
# include <semaphore.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/time.h>
# include <sys/types.h>
# include <sys/wait.h>

typedef enum e_error
{
	NO_ERROR = 0,
	ERROR_INCORRECT_NUMBER_OF_ARGUMENTS = 1,
	ERROR_ARGUMENT_IS_NOT_NUMERIC = 2,
	ERROR_INVALID_INPUT = 3,
	ERROR_FAILED_TO_INITIALIZE_FORKS = 4,
	ERROR_FAILED_TO_INITIALIZE_SEMAPHORE = 5,
	ERROR_FAILED_TO_FORK_THE_PROCESS = 6,
	ERROR_FAILED_TO_CREATE_THREAD = 7,
	ERROR_FAILED_TO_DETACH_THREAD = 8,
	ERROR_FAILED_TO_LOCK_SEMAPHORE = 9,
	ERROR_FAILED_TO_UNLOCK_SEMAPHORE = 10,
	ERROR_FAILED_TO_KILL_PROCESS = 11,
	ERROR_MALLOC_FAILED = 12
}	t_error;

typedef enum e_bool
{
	FALSE = 0,
	TRUE = 1
}					t_bool;

typedef enum e_mode
{
	GET = 0,
	SET = 1
}					t_mode;

typedef enum e_validity
{
	VALID = 0,
	INVALID = 1
}					t_validity;

typedef struct s_input
{
	int				number_of_philosophers;
	int				time_until_death;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_of_meals;
}					t_input;

typedef struct	s_semaphores
{
	sem_t			*dead;
	sem_t			*forks;
	sem_t			*print;
	sem_t			*time_of_last_meal;
	sem_t			*full;
}					t_semaphores;

typedef struct s_philosopher
{
	int				id;
	long int		time_start;
	long int		time_of_last_meal;
	pid_t			pid;
	t_input			data;
	t_bool			*dead;
	t_bool			full;
	t_semaphores	semaphores;
}					t_philosopher;

// check_input.c
t_validity			check_initial_input(const int argument_count,
						char **arguments);
t_validity			check_final_input(const int argument_count, t_input input);

// eat_sleep_think.c
void				eat_sleep_think_repeat(t_philosopher *phil);

// monitoring.c
void				*monitoring(void *ptr);

// parser.c
void				parser(const int argument_count, char **arguments,
						t_input *input);

// semaphore_initialization.c
void				initialize_semaphores(t_semaphores *semaphores,
						int number_of_philosophers);

// semaphore_utils.c
int					print_message(t_philosopher *phil, char *message, int mode);
t_bool				get_set_status(int mode, sem_t *semaphore, t_bool *status,
						t_bool new_status);
long int			get_set_time_of_last_meal(int mode, sem_t *semaphore,
						long int *time_of_last_meal,
						long int new_time_of_last_meal);

// setup_simulation.c
int					setup_simulation(t_input data,
						const int number_of_philosophers);

// start_simulation.c
void				start_simulation(t_philosopher *philosophers,
						const int number_of_philosophers);

// time.c
long int			get_time_ms(void);
long int			get_time_us(void);
void				let_time_pass(long int micro_second);

// utils.c
int					a_to_i(const char *str);
t_bool				character_is_digit(char c);
void				*ft_calloc(size_t count, size_t size);
int					skip_whitespace(const char *str);

// utils_itoa.c
char				*ft_itoa(int n);

#endif
