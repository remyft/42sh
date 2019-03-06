/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_shell_env.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/23 14:23:24 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/03/06 18:00:00 by tsisadag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
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
	if (e->progpath)
		free(e->progpath);
	sh_freetab(&e->public_env);
	sh_freetab(&e->private_env);
	sh_freetab(&e->exported_env);
	free_aliases(e->alias_list);
}
