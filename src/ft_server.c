/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_server.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-malt <ael-malt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 15:59:03 by ael-malt          #+#    #+#             */
/*   Updated: 2023/05/26 13:55:11 by ael-malt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minitalk.h"

void	signal_handler(int signal, siginfo_t *info, void *context)
{
	static int	bit;
	static int	i;

	(void) context;
	if (signal == SIGUSR2)
		i |= (0x80 >> bit);
	bit++;
	if (bit == 8)
	{
		if (i == 0)
		{
			ft_printf("\n");
			kill(info->si_pid, SIGUSR1);
		}
		else
			ft_printf("%c", i);
		bit = 0;
		i = 0;
	}
}

int	main(int argc, char **argv)
{
	struct sigaction	sa;

	(void)argv;
	if (argc != 1)
	{
		ft_printf("Error: Wrong format.\n");
		ft_printf("Try: ./server\n");
		return (0);
	}
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = &signal_handler;
	ft_printf("PID -> %d\nWaiting for a message...\n", getpid());
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (1)
		pause ();
	return (0);
}
