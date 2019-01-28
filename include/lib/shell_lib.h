/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_lib.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/27 09:51:00 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/01/28 19:27:20 by gbourgeo         ###   ########.fr       */
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
char			**sh_tabdup(const char **table);
void			sh_freestr(char **str);
void			sh_freetab(char ***table);
int				sh_putstr_fd(const char *str, int fd);
int				sh_putendl_fd(const char *str, int fd);

#endif
