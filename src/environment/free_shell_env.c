/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_shell_env.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/23 14:23:24 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/04/25 14:43:08 by dbaffier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "shell_lib.h"
#include "shell_env.h"

static void		free_aliases(t_alias *alias)
{
	if (!alias)
		return ;
	free_aliases(alias->next);
	if (alias->key)
		free(alias->key);
	if (alias->value)
		free(alias->value);
	free(alias);
}

void			free_shell_env(t_s_env *e)
{
	if (e->interactive)
		close(e->fd);
	if (e->progpath)
		free(e->progpath);
	sh_freetab(&e->public_env);
	sh_freetab(&e->private_env);
	sh_freetab(&e->exported_env);
	free_aliases(e->alias_list);
}
