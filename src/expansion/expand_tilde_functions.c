/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_tilde_functions.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/03 18:56:52 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/01/27 11:32:36 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pwd.h>
#include "libft.h"
#include "shell_lib.h"
#include "expansion_tilde.h"
#include "expansion_errors.h"

int				expand_tilde_env(t_ret *ret, const char *s, t_exp *param)
{
	(void)s;
	return (param_addstr(sh_getnenv("HOME", param->e->public_env), ret));
}

int				expand_tilde_plus(t_ret *ret, const char *s, t_exp *param)
{
	if (!s[1])
		return (param_addstr(sh_getnenv("PWD", param->e->public_env), ret));
	else if (tilde_digit(s + 1))
		return (expand_tilde_directory(ret, s + 1, param));
	return (expand_tilde_not(ret, s));
}

int				expand_tilde_minus(t_ret *ret, const char *s, t_exp *param)
{
	if (!s[1])
		return (param_addstr(sh_getnenv("OLDPWD", param->e->public_env), ret));
	else if (tilde_digit(s + 1))
		return (expand_tilde_directory(ret, s + 1, param));
	return (expand_tilde_user(ret, s, param));
}

int				expand_tilde_directory(t_ret *ret, const char *s, t_exp *param)
{
	int			entry;
	char		*cwd;

	(void)param;
	entry = ft_atoi(s);
	if (entry != 0)
		return (ERR_DIRECTORY_STACK);
	if (!(cwd = getcwd(NULL, 0)))
		return (ERR_MALLOC);
	if (param_addstr(cwd, ret))
		return (ERR_MALLOC);
	free(cwd);
	return (ERR_NONE);
}

int				expand_tilde_user(t_ret *ret, const char *s, t_exp *param)
{
	struct passwd	*user;

	(void)param;
	if ((user = getpwnam(s)) == NULL)
	{
		if (param_addstr(s, ret))
			return (ERR_MALLOC);
		return (ERR_NO_SUCH_USER);
	}
	if (param_addstr(user->pw_dir, ret))
		return (ERR_MALLOC);
	return (ERR_NONE);
}
