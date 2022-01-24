/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlatashi <mlatashi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 20:12:47 by mlatashi          #+#    #+#             */
/*   Updated: 2021/10/18 20:14:09 by mlatashi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int argc, char **argv)
{
	t_params		params;

	if (get_params(argc, argv, &params))
		return (1);
	if (init_mutex(&params))
		return (1);
	if (init_philosophers(&params))
		return (1);
	if (simulate(&params))
		return (1);
	return (0);
}
