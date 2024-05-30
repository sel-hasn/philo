/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-hasn <sel-hasn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 15:14:35 by sel-hasn          #+#    #+#             */
/*   Updated: 2024/05/25 10:52:25 by sel-hasn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philo_dead(t_philo *philo, long time_to_die)
{
	pthread_mutex_lock(&philo->philo_mtx);
	if (get_time() - philo->last_meal >= time_to_die
		&& philo->eating != true)
		return (pthread_mutex_unlock(&philo->philo_mtx), 1);
	pthread_mutex_unlock(&philo->philo_mtx);
	return (0);
}

int	ft_check_dead(t_data	*data)
{
	int	i;

	i = 0;
	while (i < data->num_philo)
	{
		if (philo_dead(&data->philos[i], data->ttd))
		{
			write_philo_actions(&data->philos[i], "died");
			pthread_mutex_lock(&data->death_mtx);
			data->death = true;
			pthread_mutex_unlock(&data->death_mtx);
			return (1);
		}
		i++;
	}
	return (0);
}

void	*monitor(void	*enf)
{
	int		i;
	t_data	*data;

	data = (t_data *)enf;
	while (1)
	{
		if (ft_check_dead(data) == 1 || data->all_full == true)
			break ;
	}
	return (NULL);
}

void	ft_creat_join_my_monitor(int what_to_do, pthread_t	*thread,
		t_data *data)
{
	if (what_to_do == 1)
	{
		if (pthread_create(thread, NULL, monitor, data) != 0)
			ft_error_find(1, data);
	}
	else if (what_to_do == 2)
	{
		if (pthread_join(*thread, NULL) != 0)
			ft_error_find(2, data);
	}
}
