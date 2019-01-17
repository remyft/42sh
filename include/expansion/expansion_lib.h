/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_lib.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/04 02:44:15 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/01/04 02:48:39 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANSION_LIB_H
# define EXPANSION_LIB_H

# include "libft.h"

int				exp_strncmp(const char *s1, const char *s2, unsigned int n);
char			*exp_getnenv(const char *name, char **env);
char			**exp_getnenvaddr(const char *name, char **env);
char			**exp_newenv(char ***env);

#endif
