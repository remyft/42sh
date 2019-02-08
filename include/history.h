/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfontain <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/07 05:31:13 by rfontain          #+#    #+#             */
/*   Updated: 2019/02/07 05:36:04 by rfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HISTORY_H
# define HISTORY_H

#include "struct.h"

# define TMP_PATH "/tmp/.21sh_history"
# define HIST_NAME ".21sh_history"

void	create_hist(t_hist **begin, char **env);
void	save_history(t_line *line, char *buff, t_hist **curr, char **env);

#endif
