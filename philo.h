/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-hasn <sel-hasn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 13:09:34 by sel-hasn          #+#    #+#             */
/*   Updated: 2024/05/25 11:57:45 by sel-hasn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <stdbool.h>
# include <sys/time.h>

typedef struct s_data	t_data;

typedef struct s_fork
{
	int				fork_id;
	pthread_mutex_t	fork_mtx;
}	t_fork;

typedef struct s_philo
{
	long			id;
	bool			full;
	t_data			*data;
	bool			eating;
	t_fork			*left_f;
	t_fork			*right_f;
	long			last_meal;
	pthread_mutex_t	philo_mtx;
	int				meals_count;
	pthread_t		philo_thread;
}	t_philo;

struct s_data
{
	long			ttd;
	long			tte;
	long			tts;
	bool			all_full;
	bool			death;
	t_fork			*forks;
	t_philo			*philos;
	pthread_t		monitor;
	long			num_philo;
	long			meals_num;
	pthread_mutex_t	mtx_write;
	pthread_mutex_t	death_mtx;
	long			start_time;
};

long	get_time(void);
long	ft_atol(char *s);
void	*monitor(void	*enf);
void	ft_clean_up(t_data *data);
void	ft_my_usleep(long to_sleep);
void	ft_philo_start(t_data *data);
void	ft_error_find(int i, t_data *data);
void	ft_get_input(char **arv, t_data *d);
int		parsing(int arc, char **arv, t_data *d);
void	write_philo_actions(t_philo *philo, char *action);
void	ft_creat_join_my_monitor(int what_to_do, pthread_t	*thread,
			t_data *data);

#endif