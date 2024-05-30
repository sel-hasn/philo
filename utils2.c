/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-hasn <sel-hasn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 16:23:25 by sel-hasn          #+#    #+#             */
/*   Updated: 2024/05/25 16:59:21 by sel-hasn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_error_find(int i, t_data *data)
{
	if (i == 1)
	{
		write(2, "can't creat thread\n", 20);
		ft_clean_up(data);
		exit(1);
	}
	else if (i == 2)
	{
		write(2, "can't join thread\n", 19);
		ft_clean_up(data);
		exit(1);
	}
}

void	ft_clean_up(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philo)
	{
		pthread_mutex_destroy(&data->forks[i].fork_mtx);
		pthread_mutex_destroy(&data->philos[i].philo_mtx);
		i++;
	}
	pthread_mutex_destroy(&data->death_mtx);
	pthread_mutex_destroy(&data->mtx_write);
	free(data->philos);
	free(data->forks);
}

void	ft_my_usleep(long to_sleep_in_usec)
{
	long	start_time;

	start_time = get_time();
	while ((get_time() - start_time) < to_sleep_in_usec)
	{
		usleep(500);
	}
}

int	cheack_dead(t_data	*data)
{
	pthread_mutex_lock(&data->death_mtx);
	if (data->death == true)
		return (pthread_mutex_unlock(&data->death_mtx), 1);
	pthread_mutex_unlock(&data->death_mtx);
	return (0);
}

void	write_philo_actions(t_philo *philo, char *action)
{
	long	actoin_time;

	pthread_mutex_lock(&philo->data->mtx_write);
	if (cheack_dead(philo->data) == 1 || philo->full)
	{
		pthread_mutex_unlock(&philo->data->mtx_write);
		return ;
	}
	actoin_time = get_time() - philo->data->start_time;
	printf("%ld %ld %s\n", actoin_time, philo->id, action);
	pthread_mutex_unlock(&philo->data->mtx_write);
}
