/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_alias_error.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/19 03:01:18 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/03/20 20:58:40 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "ft_dprintf.h"
#include "builtin_alias.h"

int		alias_error(int err, const char *cmd, const char *key, const char *prog)
{
	static char	*errors[] = {
		NULL, "malloc failed", "not found", "key not valid",
	};

	ft_dprintf(STDERR_FILENO, "%s: %s: %s: %s\n", prog, cmd, key, errors[err]);
	return (1);
}
