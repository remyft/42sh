/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/25 08:54:56 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/01/26 11:57:46 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_CD_H
# define BUILTIN_CD_H

# include "execution.h"
# include "shell_env.h"

enum
{
	ERR_NO_ERR = 0,
	ERR_MALLOC,
	ERR_INVALID_OPTION,
	ERR_TOO_MUCH_ARGUMENT,
	ERR_NO_HOME,
	ERR_NO_OLDPWD,
	ERR_NOT_IN_PWD,
};

int				cd_write_in_pwd(t_execute *exec, t_s_env *e, size_t i);
int				cd_search_in_pwd(t_execute *exec, t_s_env *e, size_t i);
int				cd_change_pwds(char *new, char *old, t_s_env *e);

int				cd_error(int err, char *arg);
int				cd_dir_error(char *newpwd, char *oldpwd, char *entry);

#endif
