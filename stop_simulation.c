/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stop_simulation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlatashi <mlatashi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 20:59:58 by mlatashi          #+#    #+#             */
/*   Updated: 2021/10/18 21:25:24 by mlatashi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	check_meals_ct(t_params *params, t_philosopher *philo)
{
	int	i;
	int	ct;

	i = 0;
	ct = 0;
	while (i < params->nbr)
	{
		if (philo[i].meals_ct >= params->meal_nbr)
			ct++;
		i++;
	}
	if (ct == params->nbr)
		params->all_alive = 0;
}

void	stop_simulation(t_params *params, t_philosopher *philo)
{
	int	i;

	while (params->all_alive)
	{
		i = 0;
		while (i < params->nbr && params->all_alive)
		{
			pthread_mutex_lock(&params->eating);
			if (get_time() - params->start_time - philo[i].last_meal
				> params->life_time)
				print_death(i, params, "died");
			pthread_mutex_unlock(&params->eating);
			usleep(100);
			i++;
		}
		if (params->meal_nbr != -1 && params->all_alive)
			check_meals_ct(params, philo);
	}
}
