/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-hasn <sel-hasn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 19:17:54 by sel-hasn          #+#    #+#             */
/*   Updated: 2024/05/25 12:02:17 by sel-hasn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->left_f->fork_mtx);
	write_philo_actions(philo, "has taken a fork");
	if (philo->data->num_philo == 1)
	{
		ft_my_usleep(philo->data->ttd);
		pthread_mutex_unlock(&philo->left_f->fork_mtx);
		return ;
	}
	pthread_mutex_lock(&philo->right_f->fork_mtx);
	write_philo_actions(philo, "has taken a fork");
	write_philo_actions(philo, "is eating");
	philo->eating = true;
	pthread_mutex_lock(&philo->philo_mtx);
	philo->last_meal = get_time();
	philo->meals_count++;
	pthread_mutex_unlock(&philo->philo_mtx);
	ft_my_usleep(philo->data->tte);
	if (philo->data->meals_num > 0
		&& philo->meals_count == philo->data->meals_num)
		philo->full = true;
	philo->eating = false;
	pthread_mutex_unlock(&philo->left_f->fork_mtx);
	pthread_mutex_unlock(&philo->right_f->fork_mtx);
}

int	ft_cheack_full_or_dead(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->death_mtx);
	if (philo->data->death == true || philo->full == true)
		return (pthread_mutex_unlock(&philo->data->death_mtx), 1);
	pthread_mutex_unlock(&philo->data->death_mtx);
	return (0);
}

void	*rotine(void	*enf)
{
	t_philo	*philo;

	philo = (t_philo *)enf;
	if (philo->data->num_philo == 1)
		ft_eat(philo);
	else
	{
		if (philo->id % 2)
			ft_my_usleep(1);
		while (!ft_cheack_full_or_dead(philo))
		{
			ft_eat(philo);
			write_philo_actions(philo, "is sleeping");
			ft_my_usleep(philo->data->tts);
			write_philo_actions(philo, "is thinking");
		}
	}
	return (NULL);
}

void	ft_creat_join_my_philos(int what_to_do, pthread_t	*thread,
		t_philo *philo)
{
	if (what_to_do == 1)
	{
		if (pthread_create(thread, NULL, rotine, philo) != 0)
			ft_error_find(1, philo->data);
	}
	else if (what_to_do == 2)
	{
		if (pthread_join(*thread, NULL) != 0)
			ft_error_find(2, philo->data);
	}
}

void	ft_philo_start(t_data *data)
{
	int	i;

	i = 0;
	ft_creat_join_my_monitor(1, &data->monitor, data);
	while (i < data->num_philo)
	{
		ft_creat_join_my_philos(1, &data->philos[i].philo_thread,
			&data->philos[i]);
		i++;
	}
	i = 0;
	while (i < data->num_philo)
	{
		ft_creat_join_my_philos(2, &data->philos[i].philo_thread,
			&data->philos[i]);
		i++;
	}
	data->all_full = true;
	ft_creat_join_my_monitor(2, &data->monitor, data);
}
