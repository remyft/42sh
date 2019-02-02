/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd_change.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/26 06:11:54 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/02/01 22:57:52 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell_lib.h"
#include "builtin_cd.h"

int			cd_change_pwds(char *new, t_s_env *e)
{
	char	*pwd;
	char	**var;

	if (!(pwd = sh_getnenv("PWD", e->public_env)))
		pwd = sh_getnenv("PWD", e->private_env);
	if (!pwd)
	{
		sh_unsetenv("OLDPWD", e->public_env);
		sh_unsetenv("OLDPWD", e->private_env);
	}
	else if ((var = sh_getnenvaddr("OLDPWD", e->public_env)))
		sh_setenv("OLDPWD", pwd, &e->public_env);
	else
		sh_setenv("OLDPWD", pwd, &e->private_env);
	if ((pwd = sh_getnenv("PWD", e->public_env)))
		sh_setenv("PWD", new, &e->public_env);
	else
		sh_setenv("PWD", new, &e->private_env);
	return (ERR_NO_ERR);
}
