/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabrigo <mabrigo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 18:08:38 by mabrigo           #+#    #+#             */
/*   Updated: 2024/05/15 18:42:57 by mabrigo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

/*
SIGUSR1 = 1
SIGUSR2 = 0
*/

void	signal_handler(int bit)
{
	static unsigned char	current_char;
	static int				bit_counter = 0;

	current_char |= (bit == SIGUSR1);
	bit_counter++;
	if (bit_counter == 8)
	{
		if (current_char == EOT)
			ft_printf(GREEN BOLD "\nend reached\n\x1b[0m");
		else
			ft_printf("%c", current_char);
		current_char = 0;
		bit_counter = 0;
	}
	else
		current_char <<= 1;
}

int	main(void)
{
	ft_printf("You're now in MABRIGO's server, welcome!\n");
	ft_printf("SERVER'S PID:" " %d\n\x1b[0m", getpid());
	while (1)
	{
		signal(SIGUSR2, signal_handler);
		signal(SIGUSR1, signal_handler);
		pause();
	}
	return (0);
}
