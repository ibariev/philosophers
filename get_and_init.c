/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_and_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlatashi <mlatashi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 20:07:34 by mlatashi          #+#    #+#             */
/*   Updated: 2021/10/18 20:07:45 by mlatashi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	check_params(const t_params *params, int argc)
{
	if (params->nbr < 1 || params->life_time < 0 || params->eating_time < 0
		|| params->sleeping_time < 0 || (argc == 6 && params->meal_nbr <= 0))
	{
		printf("Incorrect value of argument(s)\n");
		return (1);
	}
	if (params->nbr == 1)
	{
		printf("The philosopher can't eat with one fork. He died.\n");
		return (1);
	}
	return (0);
}

int	get_params(int argc, char **argv, t_params *params)
{
	if (argc < 5 || argc > 6)
	{
		printf("Incorrect number of arguments\n");
		printf("Usage: ./philo number_of_philosophers time_to_die time_to_eat");
		printf(" time_to_sleep [number_of_times_each_philosopher_must_eat]\n");
		return (1);
	}
	params->nbr = ft_atoi(argv[1]);
	params->life_time = ft_atoi(argv[2]);
	params->eating_time = ft_atoi(argv[3]);
	params->sleeping_time = ft_atoi(argv[4]);
	params->all_alive = 1;
	if (argc == 6)
		params->meal_nbr = ft_atoi(argv[5]);
	else
		params->meal_nbr = -1;
	return (check_params(params, argc));
}

int	init_mutex(t_params *params)
{
	int	i;

	params->forks = malloc(sizeof(pthread_mutex_t) * params->nbr);
	if (params->forks == NULL)
		return (print_error(1));
	i = 0;
	while (i < params->nbr)
	{
		if (pthread_mutex_init(&params->forks[i], NULL))
			return (print_error(2));
		i++;
	}
	if (pthread_mutex_init(&params->eating, NULL))
		return (print_error(2));
	if (pthread_mutex_init(&params->printing, NULL))
		return (print_error(2));
	return (0);
}

int	init_philosophers(t_params *params)
{
	int	i;

	params->philosophers = malloc(sizeof(t_philosopher) * params->nbr);
	if (params->philosophers == NULL)
		return (print_error(1));
	i = 0;
	while (i < params->nbr)
	{
		params->philosophers[i].id = i;
		params->philosophers[i].meals_ct = 0;
		params->philosophers[i].last_meal = 0;
		params->philosophers[i].params = params;
		params->philosophers[i].left = &params->forks[i];
		if (i < params->nbr - 1)
			params->philosophers[i].right = &params->forks[i + 1];
		else
			params->philosophers[i].right = &params->forks[0];
		i++;
	}
	return (0);
}
