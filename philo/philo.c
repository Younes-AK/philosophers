/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yakazdao <yakazdao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 13:26:37 by yakazdao          #+#    #+#             */
/*   Updated: 2024/07/04 10:07:41 by yakazdao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	assign_args(char **av, t_philo *philos)
{
	int	i;

	i = 0;
	while (i < ft_atol(av[1]))
	{
		philos[i].nbr_of_philos = ft_atol(av[1]);
		philos[i].time_to_die = ft_atol(av[2]);
		philos[i].time_to_eat = ft_atol(av[3]);
		philos[i].time_to_sleep = ft_atol(av[4]);
		if (av[5])
		{
			philos[i].nbr_times_to_eat = ft_atol(av[5]);
			if (ft_atol(av[5]) == 0)
				return (1);
		}
		else
			philos[i].nbr_times_to_eat = -1;
		i++;
	}
	return (0);
}

bool	check_args(char *s)
{
	int	i;

	i = 0;
	if (*s == '\0')
		return (false);
	while (s[i])
	{
		if (!(s[i] >= '0' && s[i] <= '9'))
			return (false);
		i++;
	}
	return (true);
}

bool	parsing(char **av, int ac)
{
	int	i;

	i = 0;
	if (ac != 5 && ac != 6)
	{
		ft_error("Error\ninvalid number of arguments");
		return (false);
	}
	while (i < ac - 1)
	{
		if (!check_args(av[i]) || ft_atol(av[0]) == 0)
		{
			ft_error("Error\ninvalid argument");
			return (false);
		}
		if (ft_atol(av[i]) > INT_MAX || ft_strlen(av[i]) > 10)
		{
			ft_error("Error\narg value major than int max");
			return (false);
		}
		i++;
	}
	return (true);
}

int	main(int argc, char **argv)
{
	t_data			data;
	t_philo			*philos;

	if (!parsing(argv + 1, argc))
		return (1);
	philos = (t_philo *) malloc(sizeof(t_philo) * ft_atol(argv[1]));
	if (!philos)
	{
		ft_error("Error : malloc failed allocate memory");
		return (1);
	}
	if (assign_args(argv, philos) == 1)
		return (free(philos), 1);
	data.fork_mutex = malloc(sizeof(pthread_mutex_t) * ft_atol(argv[1]));
	if (!data.fork_mutex)
	{
		ft_error("Error : malloc failed allocate memory");
		free(philos);
		return (1);
	}
	if (data_init(&data, philos) == 1)
		return (1);
}
