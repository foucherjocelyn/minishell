/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfoucher <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 12:28:47 by jfoucher          #+#    #+#             */
/*   Updated: 2022/08/12 00:23:29 by jfoucher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include "minishell.h"
#include "../builtins.h"

static long long	ft_atoll(const char *nptr)
{
	long long	result;
	int			i;

	i = 0;
	result = 0;
	if (!ft_strcmp(nptr, "-9223372036854775808"))
		return (LONG_MIN);
	if (nptr[0] == '-' || nptr[0] == '+')
		i++;
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		result *= 10;
		result += nptr[i++] - '0';
		if (result < 0)
		{
			ft_putstr_fd("minishell: exit: numeric argument required", 2);
			return (2);
		}
	}
	if (nptr[i])
		return (ft_putstr_fd("minishell: exit: numeric argument required", 2),
			2);
	if (nptr[0] == '-')
		result = -result;
	return (result);
}

int	execute_builtin_exit(char **argv, t_tab *tabs)
{
	int	exit_status;

	free_2d_tab(&tabs->env);
	free_2d_tab(&tabs->exp);
	printf("exit\n");
	rl_clear_history();
	if (argv[1] && argv[2])
	{
		ft_putstr_fd("bash: exit: too many arguments", 2);
		close_standard_fds();
		exit (1);
	}
	if (argv[1])
	{
		/*if (!ft_isstrdigit(argv[1]))
			return (ft_putstr_fd("minishell: exit: numeric argument required",
					2), exit(2), 1);*/
		exit_status = ft_atoll(argv[1]);
		free_2d_tab(&argv);
		close_standard_fds();
		exit(exit_status);
	}
	else
	{
		free_2d_tab(&argv);
		exit(g_status);
	}
}
