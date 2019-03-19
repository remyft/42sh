/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/08 04:07:17 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/03/14 18:31:06 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "ft_dprintf.h"
#include "token.h"

t_token			*token_error(int err, t_param *param)
{
	static char	*errors[] = {
		"allocating memory failed", "syntax error near unexpected token",
	};

	ft_dprintf(STDERR_FILENO, "%s: %s", param->e->progname, errors[err]);
	if (err)
		ft_dprintf(STDERR_FILENO, " `%c'", param->line[param->i]);
	write(STDERR_FILENO, "\n", 1);
	free_token(&param->head);
	return (NULLTOKEN);
}
