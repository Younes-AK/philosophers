/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yakazdao <yakazdao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 16:09:13 by yakazdao          #+#    #+#             */
/*   Updated: 2024/06/30 09:52:42 by yakazdao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <sys/time.h>
# include <sys/wait.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <pthread.h>
# include <stdbool.h>
# include <signal.h>
# include <semaphore.h>
# include <fcntl.h>
# include <limits.h>

typedef struct s_data	t_data;

typedef struct s_philo
{
	int			philo_id;
	int			meals_count;
	int			l_fork;
	int			r_fork;
	size_t		last_meal_time;
	pthread_t	observe;
	pid_t		pid;
	t_data		*data;
}	t_philo;

typedef struct s_data
{
	int				nbr_philos;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	bool			is_died;
	bool			all_full;
	int				nbr_meals_to_eat;
	size_t			start_simulation;
	sem_t			*write_sem;
	sem_t			*meals_sem;
	sem_t			*forks;
	t_philo			*philos;
}	t_data;

long	ft_atol(const char *str);
int		ft_isdigit(int c);
size_t	ft_strlen(const char *str);
int		ft_error(char *str);
int		data_init(t_data *data, char **av);
int		dinner_routine(t_data *data);
void	ft_free_destroy(t_data *data);
void	write_handle(t_data *data, int id, char *action);
size_t	get_curr_time(void);
void	ft_usleep(size_t time, t_data *data);
size_t	gap(size_t pres, size_t past);
int		error_manager(int error);
void	end_simulation(t_data *data);
void	sem_exit(t_data *data);
void	write_handle1(t_data *data, int id, char *action);
#endif