/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_standard_fds.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfoucher <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 14:08:04 by jfoucher          #+#    #+#             */
/*   Updated: 2022/08/13 18:40:50 by jfoucher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "minishell.h"

void	close_standard_fds(void)
{
	safe_close(STDIN_FILENO);
	safe_close(STDOUT_FILENO);
	safe_close(STDERR_FILENO);
}
