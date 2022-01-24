/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlatashi <mlatashi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 20:15:23 by mlatashi          #+#    #+#             */
/*   Updated: 2021/10/19 21:05:59 by mlatashi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

struct	s_params;

typedef struct s_philosopher
{
	int					id;
	int					meals_ct;
	long				last_meal;
	pthread_mutex_t		*left;
	pthread_mutex_t		*right;
	pthread_t			thread;
	struct s_params		*params;
}						t_philosopher;

typedef struct s_params
{
	int					nbr;
	int					life_time;
	int					eating_time;
	int					sleeping_time;
	int					meal_nbr;
	int					all_alive;
	long				start_time;
	pthread_mutex_t		*forks;
	pthread_mutex_t		eating;
	pthread_mutex_t		printing;
	t_philosopher		*philosophers;
}						t_params;

int		check_params(const t_params *params, int argc);
int		get_params(int argc, char **argv, t_params *params);
int		init_mutex(t_params *params);
int		init_philosophers(t_params *params);
int		simulate(t_params *params);
void	print_activity(int id, t_params *params, char *str);
void	print_death(int id, t_params *params, char *str);
void	*sim(void *philosopher);
void	eat(t_philosopher *philo);
void	stop_simulation(t_params *params, t_philosopher *philo);
void	check_meals_ct(t_params *params, t_philosopher *philo);
int		ft_atoi(const char *str);
int		print_error(int err);
long	get_time(void);
void	free_all(t_params *params, t_philosopher *philo);

#endif