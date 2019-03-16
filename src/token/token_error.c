/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/08 04:07:17 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/03/11 17:50:25 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "ft_dprintf.h"
#include "token.h"

t_token			*token_error(int err, t_param *param)
{
	static char	*errors[] = {
		"malloc failed"
	};

	ft_dprintf(STDERR_FILENO, "%s: %s.\n", param->e->progname, errors[err]);
	free_token(&param->head);
	free_quote(&param->quote);
	return (NULLTOKEN);
}
