/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlatashi <mlatashi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 20:14:23 by mlatashi          #+#    #+#             */
/*   Updated: 2021/10/19 21:06:14 by mlatashi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_atoi(const char *str)
{
	int	i;
	int	sign;
	int	nbr;

	i = 0;
	sign = 1;
	nbr = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	else if (str[i] < 48 && str[i] > 57)
		return (0);
	while (str[i] >= 48 && str[i] <= 57 && str[i] != '\0')
	{
		nbr = nbr * 10 + (int)(str[i] - 48);
		i++;
	}
	nbr *= sign;
	return (nbr);
}

int	print_error(int err)
{
	if (err == 1)
		printf("Malloc error\n");
	else if (err == 2)
		printf("Mutex error\n");
	else if (err == 3)
		printf("An error occurred during creating a thread\n");
	return (1);
}

long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	free_all(t_params *params, t_philosopher *philo)
{
	int	i;

	i = 0;
	while (i < params->nbr)
	{
		pthread_join(philo[i].thread, NULL);
		i++;
	}
	i = 0;
	while (i < params->nbr)
	{
		pthread_mutex_destroy(&params->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&params->eating);
	pthread_mutex_destroy(&params->printing);
	free(params->forks);
	free(params->philosophers);
}
