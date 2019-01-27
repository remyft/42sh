/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_lib.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/27 09:51:00 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/01/27 19:19:00 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_LIB_H
# define SHELL_LIB_H

# include <sys/types.h>

size_t			sh_tablen(const char **table);
char			*sh_getnenv(const char *name, char **env);
char			**sh_getnenvaddr(const char *name, char **env);
int				sh_strncmp(const char *s1, const char *s2, unsigned int n);
char			**sh_newenv(char ***env);
int				sh_puttab(const char **env);
int				sh_stralnum(const char *str);
char			**sh_tabdup(char **table);

#endif
