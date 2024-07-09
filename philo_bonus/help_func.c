/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yakazdao <yakazdao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 16:15:38 by yakazdao          #+#    #+#             */
/*   Updated: 2024/06/23 16:16:20 by yakazdao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	ft_error(char *msg)
{
	write(2, msg, ft_strlen(msg));
	write(2, "\n", 1);
	return (-1);
}

void	sem_exit(t_data *data)
{
	int	i;

	i = 0;
	sem_close(data->forks);
	sem_close(data->write_sem);
	sem_close(data->meals_sem);
	sem_unlink("/forks");
	sem_unlink("/write_sem");
	sem_unlink("/meals_sem");
}

void	end_simulation(t_data *data)
{
	int	i;
	int	state;

	i = 0;
	while (i < data->nbr_philos)
	{
		waitpid(-1, &state, 0);
		if (state != 0)
		{
			i = 0;
			while (i < data->nbr_philos)
			{
				kill(data->philos[i].pid, SIGKILL);
				i++;
			}
			break ;
		}
		i++;
	}
}
