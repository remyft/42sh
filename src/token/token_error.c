/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/08 04:07:17 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/04/06 18:53:22 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "ft_dprintf.h"
#include "token.h"

t_token			*token_error(int err, t_param *param)
{
	static char	*errors[] = {
		NULL, "allocating memory failed", "syntax error near unexpected token",
		"alias error near unexpected quote"
	};

	ft_dprintf(STDERR_FILENO, "%s: %s", param->e->progname, errors[err]);
	if (err == 2)
		ft_dprintf(STDERR_FILENO, " `%c'", param->line[param->i]);
	write(STDERR_FILENO, "\n", 1);
	free_token(&param->head);
	return (NULLTOKEN);
}
