/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/25 08:54:56 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/01/26 06:10:26 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_CD_H
# define BUILTIN_CD_H

enum
{
	ERR_INVALID_OPTION = 0,
	ERR_TOO_MUCH_ARGUMENT,
	ERR_NOT_IN_PWD,
};

int				cd_error(int err, char *arg);
int				cd_dir_error(char *newpwd, char *oldpwd, char *entry);
int				cd_write_in_pwd(char **args, t_s_env *e, int i);
int				cd_search_in_pwd(char **args, t_s_env *e);

#endif
