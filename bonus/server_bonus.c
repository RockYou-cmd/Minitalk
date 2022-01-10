/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-korc <ael-korc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/08 22:26:19 by ael-korc          #+#    #+#             */
/*   Updated: 2022/01/10 17:56:37 by ael-korc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"

t_data	g_data;

void	check(int pid, int oldpid)
{
	if (pid != 0 && pid != oldpid)
	{
		g_data.c = 0;
		g_data.pos = 0;
		write(1, "\n", 1);
	}
}

void	receive(int sig, siginfo_t *siginfo, void *uncontex)
{
	static pid_t	pid = 0;

	(void)uncontex;
	check(pid, siginfo->si_pid);
	if (sig == SIGUSR1)
		g_data.c |= 1 << g_data.pos;
	g_data.pos++;
	if (g_data.pos == 8)
	{
		g_data.pos = 0;
		if (!g_data.c)
		{
			ft_putchar_fd('\n', 1);
			g_data.sent = 1;
		}
		else
			ft_putchar_fd(g_data.c, 1);
		g_data.c = 0;
	}
	pid = siginfo->si_pid;
	if (g_data.sent == 1)
	{
		kill(siginfo->si_pid, SIGUSR1);
		g_data.sent = 0;
	}
}

int	main(void)
{
	struct sigaction	sa;

	sa.sa_sigaction = receive;
	sa.sa_flags = SA_RESTART;
	g_data.c = 0;
	g_data.pos = 0;
	ft_putstr_fd("PID     : ", 1);
	ft_putnbr_fd(getpid(), 1);
	ft_putchar_fd('\n', 1);
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (1)
		usleep(500);
	return (0);
}
