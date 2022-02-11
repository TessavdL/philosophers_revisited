/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philosophers.h                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: tessa <tessa@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/22 13:02:29 by tessa         #+#    #+#                 */
/*   Updated: 2022/02/11 17:04:21 by tevan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# define UNINITIALIZED -1

# define DEAD 0
# define PRINT 1

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef enum e_bool
{
	FALSE = 0,
	TRUE = 1
}					t_bool;

typedef enum e_validity
{
	VALID = 0,
	INVALID = 1
}					t_validity;

typedef struct s_fork
{
	pthread_mutex_t	*left;
	pthread_mutex_t	*right;
}					t_fork;

typedef struct s_mutexes
{
	pthread_mutex_t	*dead;
	pthread_mutex_t	*print;
	pthread_mutex_t	time_of_last_meal;
	pthread_mutex_t	full;
	t_fork			fork;
}					t_mutexes;

typedef struct s_thread
{
	pthread_t		monitoring;
	pthread_t		simulation;
}					t_thread;

typedef struct s_input
{
	int				number_of_philosophers;
	int				time_until_death;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_of_meals;
}					t_input;

typedef struct s_philosopher
{
	int				id;
	long int		time_start;
	long int		time_of_last_meal;
	t_input			data;
	t_bool			*dead;
	t_bool			full;
	t_thread		thread;
	t_mutexes		mutexes;
}					t_philosopher;

// check_input.c
t_validity			check_initial_input(const int argument_count, char **arguments);
t_validity			check_final_input(const int argument_count, t_input input);

// eat_sleep_think.c
void				*eat_sleep_think(void *ptr);

// monitoring.c
void				*monitoring(void *ptr);

// mutexes_destruction.c
void				destroy_all_shared_mutexes(pthread_mutex_t *mutexes,
						const int number_of_philosophers);
void				destroy_part_shared_mutexes(pthread_mutex_t **mutexes,
						int i);
void				destroy_all_individual_mutexes(t_philosopher *philosophers,
						const int number_of_philosophers);
void				destroy_part_individual_mutexes(t_philosopher *philosophers,
						int i);

// mutexes_initialization.c
void				assign_shared_mutexes(t_philosopher **philosophers, 
						pthread_mutex_t **shared_mutexes,
						const int number_of_philosophers);
int					initialize_individual_mutexes(t_philosopher **philosophers,
						const int number_of_philosophers);
int					initialize_shared_mutexes(pthread_mutex_t **mutexes,
						const int number_of_philosophers);

// mutexes_utils.c
int					print_message(t_philosopher *phil, long int time,
						char *message);
long int			get_time_of_last_meal(pthread_mutex_t *mutex,
						long int time_of_last_meal);
void				set_time_of_last_meal(pthread_mutex_t *mutex,
						long int *time_of_last_meal,
						long int new_time_of_last_meal);
t_bool				get_status(pthread_mutex_t *mutex, t_bool status);
void				set_status(pthread_mutex_t *mutex, t_bool *status,
						t_bool new_status);

// parser.c
void				parser(const int argument_count, char **arguments,
						t_input *input);

// setup_simulation.c
int					setup_simulation(t_input data, const int number_of_philosophers);

// start_simulation.c
int					start_simulation(t_philosopher *philosophers,
						const int number_of_philosophers);

// time.c
long int			get_time(void);
void				let_time_pass(long int total_time);

// utils.c
int					a_to_i(const char *str);
t_bool				character_is_digit(char c);
void				*ft_calloc(size_t count, size_t size);
int					skip_whitespace(const char *str);

#endif
