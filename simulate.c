/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlatashi <mlatashi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 20:27:26 by mlatashi          #+#    #+#             */
/*   Updated: 2021/10/19 21:06:48 by mlatashi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	print_activity(int id, t_params *params, char *str)
{
	pthread_mutex_lock(&params->printing);
	if (params->all_alive)
		printf("%ld %d %s\n", get_time() - params->start_time, id + 1, str);
	pthread_mutex_unlock(&params->printing);
}

void	print_death(int id, t_params *params, char *str)
{
	pthread_mutex_lock(&params->printing);
	if (params->all_alive)
		printf("%ld %d %s\n", get_time() - params->start_time, id + 1, str);
	params->all_alive = 0;
	pthread_mutex_unlock(&params->printing);
}

void	eat(t_philosopher *philo)
{
	t_params	*params;

	params = philo->params;
	pthread_mutex_lock(philo->left);
	print_activity(philo->id, params, "has taken a fork");
	pthread_mutex_lock(philo->right);
	print_activity(philo->id, params, "has taken a fork");
	pthread_mutex_lock(&params->eating);
	print_activity(philo->id, params, "is eating");
	philo->last_meal = get_time() - params->start_time;
	pthread_mutex_unlock(&params->eating);
	usleep(params->eating_time * 1000);
	philo->meals_ct += 1;
	pthread_mutex_unlock(philo->left);
	pthread_mutex_unlock(philo->right);
}

void	*sim(void *philosopher)
{
	t_philosopher	*philo;
	t_params		*params;

	philo = (t_philosopher *) philosopher;
	params = philo->params;
	if (philo->id % 2)
		usleep(20000);
	while (params->all_alive)
	{
		eat(philo);
		print_activity(philo->id, params, "is sleeping");
		usleep(params->sleeping_time * 1000);
		print_activity(philo->id, params, "is thinking");
	}
	return (NULL);
}

int	simulate(t_params *params)
{
	int				i;
	t_philosopher	*philo;	

	i = 0;
	philo = params->philosophers;
	params->start_time = get_time();
	while (i < params->nbr)
	{
		if (pthread_create(&philo[i].thread, NULL, sim, &philo[i]))
			return (print_error(3));
		i++;
	}
	stop_simulation(params, params->philosophers);
	free_all(params, params->philosophers);
	return (0);
}
