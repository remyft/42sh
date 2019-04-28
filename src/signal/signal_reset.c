/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_reset.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaffier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/29 16:07:57 by dbaffier          #+#    #+#             */
/*   Updated: 2019/04/26 18:36:59 by dbaffier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signal.h"
#include "signal_intern.h"
#include <stdio.h>

int		signal_to_default(void)
{
	if (signal(SIGINT, SIG_DFL) == SIG_ERR)
		return (1);
	if (signal(SIGQUIT, SIG_DFL) == SIG_ERR)
		return (1);
	if (signal(SIGTSTP, SIG_DFL) == SIG_ERR)
		return (1);
	if (signal(SIGTTIN, SIG_DFL) == SIG_ERR)
		return (1);
	if (signal(SIGTTOU, SIG_DFL) == SIG_ERR)
		return (1);
	if (signal(SIGCHLD, SIG_DFL) == SIG_ERR)
		return (1);
	return (0);
}
