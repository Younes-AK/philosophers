/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yakazdao <yakazdao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 16:16:56 by yakazdao          #+#    #+#             */
/*   Updated: 2024/07/04 11:29:51 by yakazdao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

size_t	gap(size_t pres, size_t past)
{
	return (pres - past);
}

void	write_handle1(t_data *data, int id, char *action)
{
	printf("%lu  %d  %s\n", get_curr_time() - data->start_simulation,
		id + 1, action);
	return ;
}

void	ft_usleep(size_t milliseconds, t_data *data)
{
	size_t	start;

	start = get_curr_time();
	while ((get_curr_time() - start) < milliseconds && !data->is_died)
		usleep(500);
}

size_t	get_curr_time(void)
{
	int				state;
	struct timeval	time;

	state = gettimeofday(&time, NULL);
	if (state == -1)
		ft_error("Error: gettimeofday failed\n");
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	write_handle(t_data *data, int id, char *action)
{
	sem_wait(data->write_sem);
	if (!(data->is_died))
	{
		printf("%lu  %d  %s\n", get_curr_time() - data->start_simulation,
			id + 1, action);
	}
	sem_post(data->write_sem);
	return ;
}
