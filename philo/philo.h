/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yakazdao <yakazdao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 21:51:27 by yakazdao          #+#    #+#             */
/*   Updated: 2024/07/04 08:35:18 by yakazdao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>
# include <unistd.h>
# include <limits.h>
# include <stdbool.h>

typedef struct s_philo
{
	int				nbr_of_philos;
	int				philo_id;
	int				nbr_meals_eaten;
	size_t			last_meal_time;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	int				nbr_times_to_eat;
	bool			is_eating_now;
	bool			*is_dead;
	size_t			start_simulation;
	pthread_t		thread;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*write_mutex;
	pthread_mutex_t	*dead_mutex;
	pthread_mutex_t	*meal_mutex;
}					t_philo;

typedef struct s_data
{
	bool			dead;
	pthread_t		observer;
	pthread_mutex_t	*fork_mutex;
	pthread_mutex_t	write_mutex;
	pthread_mutex_t	dead_mutex;
	pthread_mutex_t	meal_mutex;
	t_philo			*philos;
}	t_data;

long	ft_atol(const char *str);
size_t	ft_strlen(const char *str);
int		ft_isdigit(int c);
int		ft_error(char *msg);
int		data_init(t_data *data, t_philo *philos);
void	init_philos(t_philo *philos, t_data *program);
int		ft_usleep(size_t milliseconds, t_philo *philo);
int		init_forks(t_data *data, t_philo *philos);
size_t	get_current_time(void);
void	ft_destroy_mutex(t_data *data, int nbr_of_philos);
void	ft_write_handle(t_philo *philo, int philo_id, char *philo_state);
void	eating(t_philo *philo);
bool	check_is_dead(t_philo *philo);
void	*monitor(void *data);
#endif