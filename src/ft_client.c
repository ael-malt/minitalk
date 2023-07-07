/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_client.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-malt <ael-malt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 15:54:42 by ael-malt          #+#    #+#             */
/*   Updated: 2023/05/24 14:28:33 by ael-malt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minitalk.h"

static void	signal_handler(int signal)
{
	if (signal == SIGUSR1)
		ft_printf("Server has successfully received the message (´• ω •`)\n");
}

static void	ft_send_bits(int pid, const char *str)
{
	int					bit;
	char				c;
	struct sigaction	sa;

	sa.sa_handler = &signal_handler;
	sigaction(SIGUSR1, &sa, NULL);
	while (*str)
	{
		bit = 8;
		c = *str++;
		while (bit--)
		{
			if (c >> bit & 1)
				kill(pid, SIGUSR2);
			else
				kill(pid, SIGUSR1);
			usleep(700);
		}
	}
	while (++bit < 8 && kill(pid, SIGUSR1) == 0)
		usleep(700);
}

int	main(int argc, char **argv)
{
	char const	*str;
	int			pid;

	if (argc != 3)
	{
		ft_printf("Error: wrong format.\n");
		ft_printf("Try: ./client <PID> <MESSAGE>\n");
		return (1);
	}
	pid = ft_atoi(argv[1]);
	if (!pid)
	{
		ft_printf("Error: Invalid pid\n");
		return (0);
	}
	str = argv[2];
	ft_send_bits(pid, str);
	return (0);
}
