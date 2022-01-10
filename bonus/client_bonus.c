/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-korc <ael-korc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/08 22:26:15 by ael-korc          #+#    #+#             */
/*   Updated: 2022/01/10 19:35:46 by ael-korc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"

void	sent(int sig)
{
	if (sig == SIGUSR1)
	{
		write(1, "\033[0;32m""message sent!✅\n", 25);
		exit(1);
	}
}

void	ft_tobin(unsigned char chr, int pidserv)
{
	int	i;

	i = 0;
	if (chr < 0)
		return ;
	while (i < 8)
	{
		if (chr % 2 == 1)
			kill(pidserv, SIGUSR1);
		if (chr % 2 == 0)
			kill(pidserv, SIGUSR2);
		chr = chr / 2;
		i++;
		usleep(300);
	}
}

static void	ft_send(unsigned char *str, int pidserv)
{
	int	i;

	i = 0;
	while (str[i])
		ft_tobin(str[i++], pidserv);
	ft_tobin(0, pidserv);
}

int	main(int ac, char **av)
{
	int	pidserv;

	signal(SIGUSR1, &sent);
	if (ac != 3)
	{
		ft_putstr_fd("WRONG ARGUMENTS!", 1);
		return (1);
	}
	pidserv = atoi((char *)av[1]);
	if (!pidserv)
	{
		ft_putstr_fd("INVALID PID!", 1);
		return (1);
	}
	ft_send((unsigned char *)av[2], pidserv);
	while (1)
		usleep(200);
	return (0);
}
